#include <iostream>
#include <string>
#include <thread>
#include <cstdlib>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BROADCAST_ADDRESS "255.255.255.255"


struct ipPort
{
	std::string ip;
	int port;
};

class Network {
	int server_fd = -1;

public:
	Network(const Network&) = delete;
	Network& operator=(const Network&) = delete;
	Network() = default;
	Network(Network&& other) : server_fd(other.server_fd) {
		other.server_fd = -1;
	}

	Network(int serv_fd) : server_fd(serv_fd) {
		if (serv_fd < 0) {
			throw std::range_error("Invalid socker fd");
		}
	}

	~Network() {
		if (server_fd >= 0) {
			close(server_fd);
		}
	}

	inline int get_fd(void) const noexcept {
		return server_fd;
	}
	int operator *() {
		return server_fd;
	}
};

class User {
	std::string nickname;

public:
	User() = default;

	void input_nickname(void) {
		std::cout << "Input your nickname:\n";
		std::cin >> nickname;
	}

	inline std::string get_nickname(void) const noexcept {
		return nickname; 
	}

	inline void set_nickname(const std::string& nick) noexcept {
		nickname = nick;
	}
};

struct sockaddr_in create_recv_addr(ipPort ip_port) {
	struct sockaddr_in recv_addr = {0};
	recv_addr.sin_family = AF_INET;
	recv_addr.sin_port = htons(ip_port.port);
	inet_pton(AF_INET, ip_port.ip.c_str(), &recv_addr.sin_addr);
	return recv_addr;
}

struct sockaddr_in create_broadcast_addr(ipPort ip_port) {
	struct sockaddr_in broadcast_addr = {0};
	broadcast_addr.sin_family = AF_INET;
	broadcast_addr.sin_port = htons(ip_port.port);
	inet_pton(AF_INET, BROADCAST_ADDRESS, &broadcast_addr.sin_addr);
	return broadcast_addr;
}

ipPort get_ip_and_port(char *argv[]) {
	ipPort ip_port;
	ip_port.ip = argv[1];
	ip_port.port = atoi(argv[2]);
	return ip_port;
}

class Sender {
	struct sockaddr_in send_addr;
	int serv_fd;

public:
	Sender(const struct sockaddr_in *addr, int fd) noexcept : send_addr(*addr), serv_fd(fd) 
		{ }

	void send_message(const std::string msg) const {
		sendto(serv_fd, msg.c_str(), msg.size(), 0, (const sockaddr *)&send_addr, sizeof(send_addr));
	}

	void run(const std::string& nickname) {
		while (true) {
			std::string msg;
			std::getline(std::cin, msg);
			std::string full_msg = (nickname + ": " + msg);
			sendto(serv_fd, full_msg.c_str(), full_msg.size(), 0, (const sockaddr *)&send_addr, sizeof(send_addr));
		}
	}
};

class Reciever {
	struct sockaddr_in recv_addr;
	int server_fd;

public:
	Reciever(const struct sockaddr_in *addr, int fd) noexcept : recv_addr(*addr), server_fd(fd)
		{ }

	void run() {
		char buffer[1001];
		socklen_t fromlen = sizeof(recv_addr);
		while (true) {
			ssize_t n = recvfrom(server_fd, buffer, sizeof(buffer)-1, 0, (sockaddr *)&recv_addr, &fromlen);
			if (n > 0) {
				buffer[n] = '\0';
				char ipstr[INET_ADDRSTRLEN];
				inet_ntop(AF_INET, &recv_addr.sin_addr, ipstr, sizeof(ipstr));
				std::cout << "[" << ipstr << "]" << buffer << std::endl;
			}
		}
	}
};

int main(int argc, char *argv[]) {
	if (argc < 3) {	
		std::cout << "Template usage: ./ipv4_chat <ip> <port>" << std::endl;
		exit(1);
	
	} else {
		std::cout << argv[1] << " " << argv[2] << std::endl;
	}
	User user;
	user.input_nickname();

	Network net(socket(AF_INET, SOCK_DGRAM, 0));

	
	ipPort ip_port = get_ip_and_port(argv);
	struct sockaddr_in recv_addr = create_recv_addr(ip_port);
	struct sockaddr_in send_addr = create_broadcast_addr(ip_port);

	int optVal {1};
	if (setsockopt(*net, SOL_SOCKET, SO_BROADCAST, &optVal, sizeof(optVal)) < 0) {
		std::cout << "setsockopt SO_BROADCAST failed\n";
		exit(1);
	}

	// разрешаем повторное использование адреса
	if (setsockopt(*net, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal)) < 0) {
		std::cout << "setsockopt SO_REUSEADDR failed\n";
		exit(1);
	}

	// иногда полезно добавить SO_REUSEPORT для Linux
	if (setsockopt(*net, SOL_SOCKET, SO_REUSEPORT, &optVal, sizeof(optVal)) < 0) {
		std::cout << "setsockopt SO_REUSEPORT failed\n";
		exit(1);
	}

	// if (bind(net.get_fd(), (const sockaddr *)&recv_addr, sizeof(recv_addr))) {
	// 	std::cout << "Error bind recv_addr!\n";
	// 	exit(1);
	// }
	
	if (bind(net.get_fd(), (const sockaddr *)&send_addr, sizeof(send_addr))) {
		std::cout << "Error bind send_addr!\n";
		exit(1);
	}
	
	Sender s(&send_addr, net.get_fd());
	Reciever r(&recv_addr, net.get_fd());


	std::thread recv_thread(&Reciever::run, &r), send_thread(&Sender::run, &s, user.get_nickname());
	recv_thread.join();
	send_thread.join();
	std::cout << "FD server: " << net.get_fd() << "Username: " << user.get_nickname() << "\n";

	return 0;
}

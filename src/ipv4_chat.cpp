#include "ipv4_chat.h"

Network::Network(const struct NetworkData& net_data) : data(net_data) {
    memset(&recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(data.port);
    recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    memset(&send_addr, 0, sizeof(send_addr));
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = htons(data.port);
    send_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
}

Network::Network(const Network& net_data) {
    fd = net_data.fd;
    data = net_data.data;
    recv_addr = net_data.recv_addr;
    send_addr = net_data.send_addr;
}

Network::~Network() {
    if (fd >= 0) {
        close(fd);
    }
}

inline void Network::set_network_data(const struct NetworkData& net_data) noexcept {
    data = net_data;
}

inline struct NetworkData Network::get_network_data(void) const noexcept {
    return data;
}

inline struct sockaddr_in Network::get_recv_addr(void) const noexcept {
    return recv_addr;
}

inline struct sockaddr_in Network::get_send_addr(void) const noexcept {
    return send_addr;
}

void Network::init_socket(void) {
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) {
        throw BadInitSocket("Error fd socket!");
    }
    
    if (bind(fd, (const sockaddr *)&recv_addr, sizeof(recv_addr)) == -1) {
        throw BadInitSocket("Error bind!");
    }

    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt)) == -1) {
        throw BadInitSocket("Error setsockopt with BROADCAST!");
    }

    int reuse_opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse_opt, sizeof(reuse_opt)) == -1) {
        throw BadInitSocket("Error setsockopt with REUSEADDR!");
    }
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &reuse_opt, sizeof(reuse_opt)) == -1) {
        throw BadInitSocket("Error setsockopt with REUSEPORT!");
    }
}


void Chat::send_message(const std::string& msg) {
    std::lock_guard<std::mutex> lock(mtx);
    std::string message = ("[" + net.get_network_data().ip + "] " + data.nickname + ": " + msg);
    if (message.size() > MAX_MESSAGE_LEN) {
        std::cerr << "Error size message > MAX_MESSAGE_LEN!" << std::endl;
    } else {
        struct sockaddr_in send_addr = net.get_send_addr();
        sendto(net.get_fd(), message.c_str(), message.size(), 0, (const sockaddr *)&send_addr, sizeof(send_addr));
    }
}

void Chat::receive_message(void) {
    char buffer[MAX_MESSAGE_LEN];

    struct sockaddr_in recv_addr;
    socklen_t send_len = sizeof(recv_addr);
    
    int count = recvfrom(net.get_fd(), buffer, sizeof(buffer), 0, (sockaddr *)&recv_addr, &send_len);
    std::lock_guard<std::mutex> lock(mtx);
    if (count == -1) {
        const char *str = strerror(errno);
        std::cerr << "Error failed receive message! " << str << " " << net.get_fd() << std::endl;
        
    } else {
        buffer[count] = '\0';
        std::cout << buffer << std::endl; 
    }
}
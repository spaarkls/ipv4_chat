#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include "src/ipv4_chat.h"
#include "src/helper.h"

void thread_sender(void *arg);
void thread_recv(void *arg);

std::mutex mtx;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "Template usage: ./ipv4_chat <ip> <port>" << std::endl;
        return 1;
    }
    
    try {
        struct NetworkData ip_port = parse_args(argv);
        struct UserData user;
        std::cout << "Input nickname:\n";
        std::getline(std::cin, user.nickname);
        Network net(ip_port);
        net.init_socket();
        Chat chat(net, user);
        std::thread recv_thread(thread_recv, &chat);
        std::thread send_thread(thread_sender, &chat);
        std::cout << net.get_fd() << std::endl;
        
        recv_thread.join();
        send_thread.join();

    } catch(BadIp& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    
    } catch (BadInitSocket& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    
    } catch (BadSendMessage& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }


    return 0;
}

void thread_recv(void *arg) {
    Chat *chat = static_cast<Chat *>(arg);
    while (true) {
        chat->receive_message();
    }
}

void thread_sender(void *arg) {
    Chat *chat = static_cast<Chat *>(arg);
    while (true) {
        std::string msg;
        std::getline(std::cin, msg);
        chat->send_message(msg);
    }
}


#include <iostream>
#include <string>
#include <thread>

#include "src/helper.h"
#include "src/ipv4_chat.h"

void thread_sender(void *arg);
void thread_recv(void *arg);

int main(int argc, char *argv[]) {
  try {
    struct NetworkData ip_port = parse_args(argc, argv);
    struct UserData user;

    std::cout << "Input nickname:\n";
    std::getline(std::cin, user.nickname);
    Network net(ip_port);
    net.init_socket();
    Chat chat(net, user);
    std::thread recv_thread(thread_recv, &chat);
    std::thread send_thread(thread_sender, &chat);

    recv_thread.join();
    send_thread.join();

  } catch (const BadCountArguments &e) {
    std::cerr << e.what() << std::endl;

  } catch (const BadIp &e) {
    std::cerr << e.what() << std::endl;
    return 1;

  } catch (const BadInitSocket &e) {
    std::cerr << e.what() << std::endl;
    return 1;

  } catch (const std::exception &e) {
    std::cerr << "Other error" << std::endl;
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

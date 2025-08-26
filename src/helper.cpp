#include "helper.h"

struct NetworkData parse_args(int argc, char* argv[]) {
  if (argc != 3) {
    throw BadCountArguments("Template usage: ./ipv4_chat <ip> <port>");
  }

  if (!portIsValid(argv[2])) {
    throw BadPort("Port must be integer!");
  }

  int port = atoi(argv[2]);
  std::string ip_address = argv[1];

  struct NetworkData nd = {.ip = "", .port = -1};
  if (ipIsValid(ip_address)) {
    nd.ip = ip_address;
    nd.port = port;

  } else {
    throw BadIp("Invalid ip address!");
  }

  return nd;
}

bool ipIsValid(const std::string& ip_address) {
  int digit = 0;
  int countDot = 0;
  std::string strDigit;
  bool is_valid = true;
  for (int i = 0; i < ip_address.size() && is_valid; i++) {
    if (isdigit(ip_address[i])) {
      strDigit += ip_address[i];

    } else if (ip_address[i] == '.') {
      countDot++;
      digit = atoi(strDigit.c_str());
      if (digit > 255) {
        is_valid = false;
      }
      strDigit.clear();
    } else {
      is_valid = false;
    }
  }
  if (!strDigit.empty()) {
    digit = atoi(strDigit.c_str());
    if (digit > 255 || countDot != 3) {
      is_valid = false;
    }
  } else {
    is_valid = false;
  }

  return is_valid;
}

bool portIsValid(const std::string& port) {
  bool is_valid = true;
  for (int i = 0; i < port.size() && is_valid; i++) {
    if (!isdigit(port[i])) {
      is_valid = false;
    }
  }
  return is_valid;
}
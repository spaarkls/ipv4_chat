/**
 * @file ipv4_chat.h
 * @brief Определения классов Network и Chat для работы с UDP чатом по IPv4
 *
 * Содержит:
 *  - класс Network — Изолирует работу с UDP сокетом, инициализацию и управление
 * сетевыми данными
 *  - класс Chat — реализует отправку и приём сообщений с использованием объекта
 * Network
 */

#ifndef __IPV4_CHAT_H__
#define __IPV4_CHAT_H__
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <atomic>
#include <cstring>
#include <iostream>
#include <mutex>
#include <string>

#include "common/object.h"
#include "exceptions/exceptions.h"

/**
 * @class Network
 * @brief Класс для работы с сетевым сокетом
 */
class Network {
  int fd = -1;             /**< Дескриптор сокета */
  struct NetworkData data; /**< Данные сети */
  struct sockaddr_in recv_addr; /**< Структура для приёма сообщений */
  struct sockaddr_in send_addr; /**< Структура для отправик сообщений */

 public:
  /**
   * @brief Конструктор с инициализацией сетевых данных
   * @param net_data Сетевые данные (IP и порт)
   */
  Network(const struct NetworkData& net_data);
  Network(const Network& net_data);
  Network() = default;

  /**
   * @brief Деструктор, который закрывает сокет если он открыт
   */
  ~Network();

  /**
   * @brief Получить дескриптор сокета
   * @return Дескриптор сокета
   */
  inline int get_fd(void) const noexcept { return fd; }

  /**
   * @brief Получить сетевые данные
   * @return Структура NetworkData
   */
  inline struct NetworkData get_network_data(void) const noexcept {
    return data;
  }

  /**
   * @brief Получить адрес для приёма сообщений
   * @return Структура адреса sockaddr_in
   */
  inline struct sockaddr_in get_recv_addr(void) const noexcept {
    return recv_addr;
  }

  /**
   * @brief Получить адрес для отправки сообщений
   * @return Структура адреса sockaddr_in
   */
  inline struct sockaddr_in get_send_addr(void) const noexcept {
    return send_addr;
  }

  /**
   * @brief Установить сетевые данные
   * @param net_data Сетевые данные (IP и порт)
   */
  void set_network_data(const struct NetworkData& net_data) noexcept;

  /**
   * @brief Инициализация сокета
   * Создаёт UPD сокет, биндит его на recv_addr и включает
   * опции BROADCAST, SO_REUSEADDR, SO_REUSERPORT
   * @throws BadInitSocket если произошла ошибка при создании или инициализации
   * сокета
   */
  void init_socket(void);
};

/**
 * @class Chat
 * @brief Класс чата
 */
class Chat {
  std::mutex mtx; /**< Mutex для синхронизации */
  Network& net; /**< Сетевой объект для работы с сокетом */
  UserData data; /**< Данные пользователя */
 public:
  /**
   * @brief Конструктор чата
   * @param net Объект Network
   * @param user Данные о пользователе
   */
  Chat(Network& net, const UserData& user) : net(net), data(user) {}

  /**
   * @brief Отправка сообщения
   * @param Строка сообщения
   */
  void send_message(const std::string& msg);

  /**
   * @brief Приём сообщения
   * Получает сообщение с сокета и выводит его в консоль
   */
  void receive_message();
};

#endif
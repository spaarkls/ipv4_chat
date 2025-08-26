/**
 * @file exceptions.h
 * @brief Определения пользовательских классов исключений для обработки ошибок
 *
 * Содержит набор исключений, унаследованных от std::exception:
 *  - BadIp - некорректный IP адрес
 *  - BadCountArguments - неверное количество аргументов
 *  - BadInitSocket - ошибка инициализации сокета
 *  - BadPort - некорректный порт
 */

#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__
#include <iostream>
#include <string>

/**
 * @class BadIp
 * @brief Исключение, возникающее при использовании некорректного IP адреса
 *
 * Наследуется от std::exception
 */
class BadIp : public std::exception {
  std::string msg_error; /**< Текст ошибки */

 public:
  /**
   * @brief Конструктор исключения
   * @param msg Строка с описанием ошибки
   */
  BadIp(const std::string msg) : msg_error(msg) {}

  /**
   * @brief Возвращает описание ошибки
   * @return C-строка с сообщением ошибки
   */
  virtual const char *what(void) const noexcept override;
};

/**
 * @class BadPort
 * @brief Исключение если при использовании некорректного порта
 *
 * Наследуется от std::exception
 */
class BadPort : public std::exception {
  std::string msg_error; /**< Текст ошибки */

 public:
  /**
   * @brief Конструктор исключения
   * @param msg Строка с описанием ошибки
   */
  BadPort(const std::string msg) : msg_error(msg) {}

  /**
   * @brief Возвращает описание ошибки
   * @return C-строка с сообщением ошибки
   */
  virtual const char *what(void) const noexcept override;
};

/**
 * @class BadCountArguments
 * @brief Исключение для неверного количества аргументов
 *
 * Наследуется от std::exception
 */
class BadCountArguments : public std::exception {
  std::string msg_error; /**< Текст ошибки */

 public:
  /**
   * @brief Конструктор исключения
   * @param msg Строка с описанием ошибки
   */
  BadCountArguments(const std::string msg) : msg_error(msg) {}

  /**
   * @brief Возвращает описание ошибки
   * @return C-строка с сообщением ошибки
   */
  virtual const char *what(void) const noexcept override;
};

/**
 * @class BadInitSocket
 * @brief Исключение при неудачной инициализации сокета
 *
 * Наследуется от std::exception
 */
class BadInitSocket : public std::exception {
  std::string msg_error; /**< Текст ошибки */

 public:
  /**
   * @brief Конструктор исключения
   * @param msg Строка с описанием ошибки
   */
  BadInitSocket(const std::string msg) : msg_error(msg) {}

  /**
   * @brief Возвращает описание ошибки
   * @return C-строка с сообщением ошибки
   */
  virtual const char *what(void) const noexcept override;
};

#endif  // __EXCEPTIONS_H__

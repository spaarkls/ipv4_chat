#ifndef __OBJECT_H__
#define __OBJECT_H__
#include <iostream>
#include <string>

constexpr int MAX_MESSAGE_LEN = 1000; /**< Максимальная длина сообщения */
constexpr const char* BROADCAST = "255.255.255.255"; /**< Адрес для шировоквещательной рассылки */

/**
 * @brief Структура для хранения информации о пользователе
 */
struct UserData {
    std::string nickname; /**< Ник пользователя */
};

/**
 * @brief Структура для хренения сетевых данных
 */
struct NetworkData {
    std::string ip; /**< IP адрес для приёма сообщений */
    int port; /**< Порт для приёма и отправки сообщений */
};

#endif
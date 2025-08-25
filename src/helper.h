#ifndef __HELPER_H__
#define __HELPER_H__
#include "common/object.h"
#include "exceptions/exceptions.h"

/**
 * @brief Парсит аргументы командной строки в структуру NetworkData
 * 
 * Извлекает IP адрес и порт из массива argv и проверяет корректность IP.
 * Если IP некорректный, выбрасывает исключение BadIp.
 * 
 * @param argv Массив аргументов командной строки (argv[1] - IP, argv[2] - порт)
 * @return Структура NetworkData (IP и порт)
 * @throws BadIp Если переданный IP адрес невалиден
 */
struct NetworkData parse_args(char *argv[]);


/**
 * @brief Проверяет корректность IPv4-адреса
 * 
 * @param ip_address Строка с предполагаемым IP-адресом
 * @return true Если IP валиден
 * @return false Если IP невалиден
 */
bool ipIsValid(const std::string& ip_address);

#endif
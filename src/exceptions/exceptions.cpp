#include "exceptions.h"


const char *BadIp::what(void) const noexcept {
    return msg_error.c_str();
}

const char *BadCountArguments::what(void) const noexcept {
    return msg_error.c_str();
}

const char *BadInitSocket::what(void) const noexcept {
    return msg_error.c_str();
}

const char *BadSendMessage::what(void) const noexcept {
    return msg_error.c_str();
}
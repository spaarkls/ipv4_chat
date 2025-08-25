#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__
#include <iostream>
#include <string>

class BadIp : public std::exception {
    std::string msg_error;

public:
    BadIp(const std::string msg) : msg_error(msg)
        { }

    virtual const char *what(void) const noexcept override;
};


class BadCountArguments : public std::exception {
    std::string msg_error;

public:
    BadCountArguments(const std::string msg) : msg_error(msg)
        { }

    virtual const char *what(void) const noexcept override;
};


class BadInitSocket : public std::exception {
    std::string msg_error;

public:
    BadInitSocket(const std::string msg) : msg_error(msg) 
        { }

    virtual const char *what(void) const noexcept override;
};


class BadSendMessage : public std::exception {
    std::string msg_error;

public:
    BadSendMessage(const std::string msg) : msg_error(msg)
        { }
    
    virtual const char *what(void) const noexcept override;
};

#endif

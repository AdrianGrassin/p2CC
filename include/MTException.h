#ifndef MTEXCEPTION_H
#define MTEXCEPTION_H

#include <exception>
#include <string>

/**
 * Excepción personalizada para errores de validación de Máquina de Turing
 */
class MTException : public std::exception {
private:
    std::string message;

public:
    explicit MTException(const std::string& msg) : message(msg) {}
    
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // MTEXCEPTION_H

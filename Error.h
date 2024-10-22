#ifndef ERRORS_H
#define ERRORS_H

#include <string>

struct Error {
    int code;
    std::string message;
};

//1XX related to Database
const Error ERROR_100 = {101, "Error 100: No encontrado."};
const Error ERROR_101 = {101, "Error 101: Cliente existente."};
const Error ERROR_102 = {102, "Error 102: Cliente inexistente."};

#endif // ERRORS_H


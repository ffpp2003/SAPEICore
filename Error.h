#ifndef ERRORS_H
#define ERRORS_H

#include <string>

#define DATABASE_ERROR 0
#define SERVER_ERROR 0

const std::string errLib[][98] = {
    {
        //DATABASE_ERROR
        "Cliente no encontrado",        //001
        "Vehiculo no encontrado",       //002
        "Cliente existente",            //003
        "Vehiculo existente",           //004
    },
    {
        //SERVER_ERROR
    }
};

std::string getErrMsg(int error){
    int errType = error / 100;
    int errId = error % 100 - 1;
    return errLib[errType][errId];
}

#endif // ERRORS_H


#ifndef ERRORS_H
#define ERRORS_H

#include <string>

enum errorCode{
    //Database errors
    DB_CLIENT_NOT_FOUND = 1,
    DB_VEHICLE_NOT_FOUND,
    DB_DUPLICATE_CLIENT,
    DB_DUPLICATE_VEHICLE,
    //Client Errors
    CL_SERVER_TIMEOUT = 100,
};


const std::string errLib[][99] = {
    {
        //DATABASE_ERROR [000 - 099]
        "Cliente no encontrado",        //000
        "Vehiculo no encontrado",       //001
        "Cliente existente",            //002
        "Vehiculo existente",           //003
    },
    {
        //CLIENT_ERROR  [100 - 199]
        "No se pudo conectar con el servidor"
    }
};

inline std::string getErrMsg(int error){
    int errType = error / 100;
    int errId = error % 100;
    return errLib[errType][errId];
}

#endif // ERRORS_H



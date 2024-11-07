#ifndef ERRORS_H
#define ERRORS_H

#include <string>

enum errorCode{
    OK,
    //Database errors
    DB_CLIENT_NOT_FOUND = 1,
    DB_VEHICLE_NOT_FOUND,
    DB_DUPLICATE_CLIENT,
    DB_DUPLICATE_VEHICLE,
    //Client Errors
    CL_SERVER_TIMEOUT = 100,
    //Vehicle Errors
    VH_CLIENT_ASSOCIATE = 200,
};


const std::string errLib[][99] = {
    {
        "OK",
        //DATABASE_ERROR [001 - 099]
        "Cliente no encontrado",
        "Vehiculo no encontrado",
        "Cliente existente",
        "Vehiculo existente",
    },
    {
        //CLIENT_ERROR  [100 - 199]
        "No se pudo conectar con el servidor"
    },
    {
        //VEHICLE_ERROR  [200 - 299]
        "Este vehiculo ya tiene un cliente asociado"
    }
};

inline std::string getErrMsg(int error){
    int errType = error / 100;
    int errId = error % 100;
    return errLib[errType][errId];
}

#endif // ERRORS_H



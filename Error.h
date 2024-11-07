#ifndef ERRORS_H
#define ERRORS_H

#include <string>

enum errorCode{
    //Database errors
    DB_CLIENT_NOT_FOUND,
    DB_VEHICLE_NOT_FOUND,
    DB_DUPLICATE_CLIENT,
    DB_DUPLICATE_VEHICLE,
    //Client Errors
    CL_SERVER_TIMEOUT = 100,
    //Vehicle Errors
    VH_CLIENT_ASSOCIATE = 200,
};

// enumRange es el rango en donde hay enums definidos, donde se consideran
// pares de numeros para el rango, siendo el primero el limite inferior y
// el segundo el limite superior (NO EXCLUYENTES). "errLib" debe contener
// al menos una cadena vacia para asignar un espacio en el arreglo. En caso
// de no tener cadenas, el rango de aquellas debera ser excluido de enumRange
const int enumRange[] = {0, 3, 100, 100, 200, 200};

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
    },
    {
        //VEHICLE_ERROR  [200 - 299]
        "Este vehiculo ya tiene un cliente asociado"
    }
};

inline std::string getErrMsg(int error){
    for(int i = 0; i<(sizeof(enumRange)/sizeof(*enumRange)); i += 2) {
        if(enumRange[i] <= error && enumRange[i+1] >= error){
            int errType = error / 100;
            int errId = error % 100;
            return errLib[errType][errId];
        }
    }
    return "NO_ERR_MSG";
}

#endif // ERRORS_H



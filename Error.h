#ifndef ERRORS_H
#define ERRORS_H

#include <string>

enum errorCode{
    OK,
    //Database errors
    DB_LI = 1,
    DB_CLIENT_NOT_FOUND = DB_LI,
    DB_VEHICLE_NOT_FOUND,
    DB_DUPLICATE_CLIENT,
    DB_DUPLICATE_VEHICLE,
    DB_LS = DB_DUPLICATE_VEHICLE,
    //Client Errors
    CL_LI = 100,
    CL_SERVER_TIMEOUT = CL_LI,
    CL_LS = CL_SERVER_TIMEOUT,
    //Vehicle Errors
    VH_LI = 200,
    VH_CLIENT_ASSOCIATE = VH_LI,
    VH_LS = VH_CLIENT_ASSOCIATE,
    //Terminal errors (for)
    TR_NOT_ENOUGH_FUNDS = 300,
    TR_JUST_ENOUGH_FUNDS,
    TR_CLIENT_NOT_FOUND,
    TR_ERROR
};

// enumRange es el rango en donde hay enums definidos, donde se consideran
// pares de numeros para el rango, siendo el primero el limite inferior y
// el segundo el limite superior (NO EXCLUYENTES). "errLib" debe contener
// al menos una cadena vacia para asignar un espacio en el arreglo. En caso
// de no tener cadenas, el rango de aquellas debera ser excluido de enumRange
extern const int enumRange[];
extern const std::string errLib[][99];

bool checkEnumRange(int error);
std::string getErrMsg(int error);

#endif // ERRORS_H



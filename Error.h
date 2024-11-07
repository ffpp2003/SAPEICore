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
};

// enumRange es el rango en donde hay enums definidos, donde se consideran
// pares de numeros para el rango, siendo el primero el limite inferior y
// el segundo el limite superior (NO EXCLUYENTES). "errLib" debe contener
// al menos una cadena vacia para asignar un espacio en el arreglo. En caso
// de no tener cadenas, el rango de aquellas debera ser excluido de enumRange
const int enumRange[] = {DB_LI, DB_LS, CL_LI, CL_LS, VH_LI, VH_LS};

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
    },
    {
        //TERMINAL_ERROR [300 - 399]
        // No tiene sentido que haya cadenas. La terminal no tiene pantalla.
        "",
    }
};

bool checkEnumRange(int error){
    for(int i = 0; i<(sizeof(enumRange)/sizeof(*enumRange)); i += 2) {
        if(enumRange[i] <= error && enumRange[i+1] >= error)
            return true;
    }
    return false;
}

std::string getErrMsg(int error){
    if (checkEnumRange(error) == 0)
        return "NO_ERR_MSG";

    int errType = error / 100;
    int errId = error % 100;
    return errLib[errType][errId];
}

#endif // ERRORS_H



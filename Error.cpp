#include "Error.h"

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
        // Debe existir la cadena "" para que se ocupe el espacio y se pueda
        // indexar el arreglo de strings.
        ""
    }
};

const int enumRange[] = {DB_LI, DB_LS, CL_LI, CL_LS, VH_LI, VH_LS};


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

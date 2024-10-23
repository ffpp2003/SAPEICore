#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <sqlite3.h>
#include <string>
#include "Client.h"
#include "Vehicle.h"

/**
 * @brief Clase para administrar la base de datos
 *
 * Esta clase utiliza la SQLite3 para almacenar los datos de los clientes
 * Permite facilmente interactuar mediante la clase Client
 *
 */
class DataBase {
private:
    sqlite3* db; /**<Puntero para interactuar con la base de datos*/
    char* errMsg = 0; /**<Cadena para guardar los mensajes de error*/
    void createClientTable();
    void createVehicleTable();
    static int callback(void* data, int argc, char** argv, char** azColName);

public:
    DataBase(const std::string& dbName);
    ~DataBase();

    void addClient(const Client&);
    void rmClient(int id);
    void showClientById(const int);
    void showClientByName(const std::string&);
    void showClients();
    Client getClientById(int id);
    Client getClientByName(std::string name);

    void addVehicle(int client_id, const Vehicle&);
    void rmVehicle(const std::string& license);
    void showVehicles();
    void showVehicleByLicense(const std::string& license);
    void showVehiclesByClientId(int client_id);
};

#endif // DATABASE_H
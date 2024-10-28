#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>
#include <sqlite3.h>
#include <string>
#include <fstream>
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
    void addVehicle(const unsigned long long client_id, const Vehicle&);
    void addMultipleVehicles(const unsigned long long client_id, const std::vector<Vehicle>&);
    void createVehicleTable();
    void exportTableToCSV(const std::string& tableName, const std::string& outputFile);
    static int callback(void* data, int argc, char** argv, char** azColName);

public:
    DataBase(const std::string& dbName = "SAPEI.db");
    ~DataBase();

    void addClient(const Client&);
    void rmClient(const unsigned long long id);
    void showClientById(const unsigned long long);
    void showClientByName(const std::string&);
    void showClients();
    void updateBalance(const unsigned long long id, double balance);
    double getBalance(const unsigned long long id);
    Client getClientById(const unsigned long long id);
    Client getClientByName(std::string name);

    void rmVehicle(const std::string& license);
    void showVehicles();
    void showVehicleByLicense(const std::string& license);
    void showVehiclesByClientId(const unsigned long long client_id);

    void exportClientsToCSV(const std::string& = "clientes.csv");
    void exportVehiclesToCSV(const std::string& = "vehiculos.csv");
};

#endif // DATABASE_H

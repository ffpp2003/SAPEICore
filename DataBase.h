#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <sqlite3.h>
#include <string>
#include "Client.h"
#include "Vehicle.h"

class DataBase {
private:
    sqlite3* db;
    char* errMsg = 0;
    void createClientTable();
    void createVehicleTable();

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

    static int callback(void* data, int argc, char** argv, char** azColName);
};

#endif // DATABASE_H

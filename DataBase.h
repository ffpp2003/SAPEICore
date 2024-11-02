#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>
#include <sqlite3.h>
#include <string>
#include <fstream>
#include "Client.h"
#include "Vehicle.h"
#include "Error.h"

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

    template <typename T>
    int checkExistence(const std::string& table, const std::string& by, T value);
public:
    DataBase(const std::string& dbName = "SAPEI.db");
    ~DataBase();

    void addClient(const Client&);
    int updateClient(const Client&);
    void rmClient(const unsigned long long id);
    void showClientById(const unsigned long long);
    void showClientByName(const std::string&);
    void showClients();
    void updateBalance(const unsigned long long id, double balance);
    double getBalance(const unsigned long long id);
    Client getClientById(const unsigned long long id);
    Client getClientByName(std::string name);
    std::vector<Client> getClients();
    std::vector<Vehicle> getVehicleById(unsigned long long vehicleId); 
    std::vector<Vehicle> getVehicleByName(const std::string& vehicleName); 
    std::vector<Vehicle> getVehicles();

    void rmVehicle(const std::string& license);
    void showVehicles();
    void showVehicleByLicense(const std::string& license);
    void showVehiclesByClientId(const unsigned long long client_id);

    void exportClientsToCSV(const std::string& = "clientes.csv");
    void exportVehiclesToCSV(const std::string& = "vehiculos.csv");
};

template <typename T>
int DataBase::checkExistence(const std::string& table, const std::string& by, T value) {
    sqlite3_stmt* stmt;
    int exists = 0;
    std::string sqlSmtp = "SELECT 1 FROM " + table + " WHERE " + by + " = ";

    if constexpr (std::is_same<T, std::string>::value){
        sqlSmtp = sqlSmtp +  "'" + value + "'";
    } else if constexpr (std::is_pointer<T>::value){
        sqlSmtp = sqlSmtp +  "'" + std::string(value) + "'";
    } else if constexpr (std::is_floating_point<T>::value || std::is_integral<T>::value){
        sqlSmtp = sqlSmtp +  std::to_string(value);
    } else {
        std::cerr << "Tipo de dato no soportado." << std::endl;
        return -1;
    }

    if (sqlite3_prepare_v2(db, sqlSmtp.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) exists = 1;

    sqlite3_finalize(stmt);
    return exists;
}

#endif // DATABASE_H

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

    template <typename T>
    Client getClient(const std::string&, T);
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
    Client getClientByDni(unsigned int dni);

    std::vector<Vehicle> getVehiclesByClientId(unsigned long long vehicleId);
    std::vector<Vehicle> getVehiclesByClientName(const std::string& vehicleName);

    std::vector<Client> getAllClients();
    std::vector<Vehicle> getAllVehicles();

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
    } else if constexpr (std::is_same<T, const char*>::value || std::is_same<T, char*>::value){
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

/**
 * @brief Busca a travez de calquier atributo un cliente en la tabla.
 *
 * Devuelve un NULLCLIENT si el cliente no es encontrado.
 *
 * @param atribute Atributo para la busqueda (dni, id, etc).
 * @param value Valor del atributo seleccionado para la busqueda.
 */
template <typename T>
Client DataBase::getClient(const std::string& atribute, T value) {
    if(!checkExistence("client", atribute, value)){
        std::cerr << getErrMsg(DB_CLIENT_NOT_FOUND) << std::endl;
        return NULLCLIENT;
    }

    sqlite3_stmt* stmt;
    std::string sqlQuery =
        "SELECT client.id, client.name, client.age, client.dni, client.address, client.email, client.phone, "
        "vehicle.license, vehicle.type, vehicle.color, vehicle.brand, vehicle.model, "
        "client.balance "
        "FROM client "
        "LEFT JOIN vehicle ON client.id = vehicle.client_id WHERE client." + atribute + " = ";

    if constexpr (std::is_same<T, std::string>::value){
        sqlQuery = sqlQuery +  "'" + value + "'";
    } else if constexpr (std::is_same<T, const char*>::value || std::is_same<T, char*>::value){
        sqlQuery = sqlQuery +  "'" + std::string(value) + "'";
    } else if constexpr (std::is_floating_point<T>::value || std::is_integral<T>::value){
        sqlQuery = sqlQuery +  std::to_string(value);
    } else {
        std::cerr << "Tipo de dato no soportado." << std::endl;
        return 0;
    }

    if (sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << sqlite3_errmsg(db);
    }

    Client client;
    bool clientInitialized = false;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        if (!clientInitialized) {
            unsigned long long clientId = sqlite3_column_int64(stmt, 0);
            std::string clientName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            unsigned int age = sqlite3_column_int(stmt, 2);
            unsigned int dni = sqlite3_column_int(stmt, 3);
            std::string address(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
            std::string email(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
            std::string phone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
            double balance = sqlite3_column_double(stmt, 12);

            client = Client(clientId, clientName, age, dni, address, email, phone);
            client.setBalance(balance);
            clientInitialized = true;
        }

        const unsigned char* licenseText = sqlite3_column_text(stmt, 7);
        if (licenseText != nullptr) {
            std::string license(reinterpret_cast<const char*>(licenseText));
            std::string type(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
            std::string color(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
            std::string brand(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));
            std::string model(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 11)));

            Vehicle vehicle(license, type, color, brand, model);
            client.addVehicle(vehicle);
        }
    }

    sqlite3_finalize(stmt);

    return client;
}

#endif // DATABASE_H

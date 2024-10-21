#include "DataBase.h"

using namespace std;

DataBase::DataBase(const string& dbName) {
    if (sqlite3_open(dbName.c_str(), &db)) {
        string errorMsg = "Error opening database: ";
        errorMsg += sqlite3_errmsg(db);
        throw runtime_error(errorMsg);
    } else {
        cout << "Database opened successfully." << endl;
    }
    createClientTable();
    createVehicleTable();
}

DataBase::~DataBase() {
    sqlite3_close(db);
}

void DataBase::createClientTable(){
    const char* sqlCreateClientTable =
        "CREATE TABLE IF NOT EXISTS client ("
        "id INTEGER PRIMARY KEY,"
        "name TEXT NOT NULL,"
        "age INTEGER NOT NULL,"
        "address TEXT,"
        "email TEXT,"
        "phone TEXT"
        "); ";

    if (sqlite3_exec(db, sqlCreateClientTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

void DataBase::createVehicleTable(){
    const char* sqlCreateVehicleTable =
        "CREATE TABLE IF NOT EXISTS vehiculo ("
        "license TEXT PRIMARY KEY,"
        "client_id INTEGER NOT NULL,"
        "type TEXT,"
        "color TEXT,"
        "brand TEXT,"
        "model TEXT,"
        "FOREIGN KEY(client_id) REFERENCES client(id)"
        "); ";

    if (sqlite3_exec(db, sqlCreateVehicleTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

void DataBase::addVehicle(int client_id, const Vehicle& vh) {
    string sqlInsertar = "INSERT INTO vehiculo (license, client_id, type, color, brand, model) VALUES ('" +
        vh.getLicensePlate() + "', " + to_string(client_id) + ", '" + vh.getType() + "', '" + vh.getColor() +
        "', '" + vh.getBrand() + "', '" + vh.getModel() + "');";

    if (sqlite3_exec(db, sqlInsertar.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

void DataBase::rmVehicle(const string& license) {
    string sqlRmVehicle = "DELETE FROM vehiculo WHERE license = '" + license + "';";
    if (sqlite3_exec(db, sqlRmVehicle.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

void DataBase::showVehicles() {
    if (sqlite3_exec(db, "SELECT * FROM vehiculo;", callback, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

void DataBase::showVehicleByLicense(const string& license) {
    string sql = "SELECT * FROM vehiculo WHERE license = '" + license + "';";

    if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

void DataBase::showVehiclesByClientId(int client_id) {
    string sql = "SELECT * FROM vehiculo WHERE client_id = " + to_string(client_id) + ";";

    if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

void DataBase::addClient(const Client& cl) {
    string sqlInsertar = "INSERT INTO client (name, age, address, email, phone) VALUES ('" + cl.getName() + "', " + 
        to_string(cl.getAge()) + ", '" + cl.getAddress() + "', '" + cl.getEmail() + "', '" + cl.getPhone() + "');";

    addVehicle(cl.getId(),cl.getVehicle());

    if (sqlite3_exec(db, sqlInsertar.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

void DataBase::rmClient(int id) {
    string sqlRmClient = "DELETE FROM client WHERE id = " + to_string(id) + ";";
    if (sqlite3_exec(db, sqlRmClient.c_str(), 0, 0, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

void DataBase::showClients() {
    if (sqlite3_exec(db, "SELECT * FROM client;", callback, nullptr, &errMsg) != SQLITE_OK);
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
}

void DataBase::showClientById(const int id) {
    string sql = "SELECT * FROM client WHERE id = " + to_string(id) + ";";

    if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &errMsg) != SQLITE_OK) {
        cerr << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

void DataBase::showClientByName(const string& name) {
    string sql = "SELECT * FROM client WHERE name = '" + name + "';";

    if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &errMsg) != SQLITE_OK) {
        cerr << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

int DataBase::callback(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << " | ";
    }
    cout << endl;
    return 0;
}

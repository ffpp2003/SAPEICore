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
        "CREATE TABLE IF NOT EXISTS vehicle ("
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
    string sqlInsertar = "INSERT OR IGNORE INTO vehicle (license, client_id, type, color, brand, model) VALUES ('" +
        vh.getLicensePlate() + "', " + to_string(client_id) + ", '" + vh.getType() + "', '" + vh.getColor() +
        "', '" + vh.getBrand() + "', '" + vh.getModel() + "');";

    if (sqlite3_exec(db, sqlInsertar.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

void DataBase::rmVehicle(const string& license) {
    string sqlRmVehicle = "DELETE FROM vehicle WHERE license = '" + license + "';";
    if (sqlite3_exec(db, sqlRmVehicle.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

void DataBase::showVehicles() {
    if (sqlite3_exec(db, "SELECT * FROM vehicle;", callback, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

void DataBase::showVehicleByLicense(const string& license) {
    string sql = "SELECT * FROM vehicle WHERE license = '" + license + "';";

    if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

void DataBase::showVehiclesByClientId(int client_id) {
    string sql = "SELECT * FROM vehicle WHERE client_id = " + to_string(client_id) + ";";

    if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

void DataBase::addClient(const Client& cl) {
    string sqlInsertar = "INSERT OR IGNORE INTO client (name, age, address, email, phone) VALUES ('" + cl.getName() + "', " +
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
    if (sqlite3_exec(db, "SELECT * FROM client;", callback, nullptr, &errMsg) != SQLITE_OK){
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

void DataBase::showClientById(const int id) {
    string sql = "SELECT * FROM client WHERE id = " + to_string(id) + ";";

    if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

void DataBase::showClientByName(const string& name) {
    string sql = "SELECT * FROM client WHERE name = '" + name + "';";

    if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
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

Client DataBase::getClientById(int id) {
    sqlite3_stmt* stmt;
    const char* sqlQuery =
        "SELECT client.id, client.name, client.age, client.address, client.email, client.phone, "
        "vehicle.license, vehicle.type, vehicle.color, vehicle.brand, vehicle.model "
        "FROM client "
        "LEFT JOIN vehicle ON client.id = vehicle.client_id "
        "WHERE client.id = ?;";

    if (sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, nullptr) != SQLITE_OK) {
        throw runtime_error(sqlite3_errmsg(db));
    }

    sqlite3_bind_int(stmt, 1, id);
    Client client;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int clientId = sqlite3_column_int(stmt, 0);
        string name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        int age = sqlite3_column_int(stmt, 2);
        string address(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        string email(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        string phone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));

        string license(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        string type(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        string color(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        string brand(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
        string model(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));

        client = Client(clientId, name, age, address, email, phone, license, type, color, brand, model);
    }

    sqlite3_finalize(stmt);

    return client;
}

Client DataBase::getClientByName(string name) {
    sqlite3_stmt* stmt;
    const char* sqlQuery =
        "SELECT client.id, client.name, client.age, client.address, client.email, client.phone, "
        "vehicle.license, vehicle.type, vehicle.color, vehicle.brand, vehicle.model "
        "FROM client "
        "LEFT JOIN vehicle ON client.id = vehicle.client_id "
        "WHERE client.name = ?;";

    if (sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, nullptr) != SQLITE_OK) {
        throw runtime_error(sqlite3_errmsg(db));
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    Client client;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int clientId = sqlite3_column_int(stmt, 0);
        string name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        int age = sqlite3_column_int(stmt, 2);
        string address(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        string email(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        string phone(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));

        string license(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
        string type(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        string color(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));
        string brand(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)));
        string model(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));

        client = Client(clientId, name, age, address, email, phone, license, type, color, brand, model);
    }

    sqlite3_finalize(stmt);

    return client;
}

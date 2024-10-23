#include "DataBase.h"

using namespace std;

/**
 * @brief Abre la base de datos
 *
 * Abre la base de datos con el nombre proporcionado y crea las tablas de cliente y vehículo.
 *
 * @param dbName Nombre del archivo de la base de datos.
 * @throws runtime_error Si hay un error al abrir la base de datos.
 */
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

/**
 * @brief Cierra la conexión a la base de datos.
 */
DataBase::~DataBase() {
    sqlite3_close(db);
}

/**
 * @brief Crea la tabla de clientes en la base de datos.
 *
 * La tabla solo se crea si no existe.
 *
 * @throws runtime_error Si hay un error al crear la tabla.
 */
void DataBase::createClientTable(){
    const char* sqlCreateClientTable =
        "CREATE TABLE IF NOT EXISTS client ("
        "id INTEGER PRIMARY KEY,"
        "balance REAL NOT NULL,"
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

/**
 * @brief Crea la tabla de vehículos en la base de datos.
 *
 * La tabla solo se crea si no existe.
 *
 * @throws runtime_error Si hay un error al crear la tabla.
 */
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

/**
 * @brief Agrega un vehículo a la base de datos.
 *
 * Si el vehículo ya existe, no se insertará.
 *
 * @param client_id ID del cliente asociado al vehículo.
 * @param vh Objeto de tipo Vehicle que contiene la información del vehículo a agregar.
 * @throws runtime_error Si hay un error al insertar el vehículo.
 */
void DataBase::addVehicle(int client_id, const Vehicle& vh) {
    string sqlInsertar = "INSERT OR IGNORE INTO vehicle (license, client_id, type, color, brand, model) VALUES ('" +
        vh.getLicensePlate() + "', " + to_string(client_id) + ", '" + vh.getType() + "', '" + vh.getColor() +
        "', '" + vh.getBrand() + "', '" + vh.getModel() + "');";

    if (sqlite3_exec(db, sqlInsertar.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

/**
 * @brief Elimina un vehículo de la base de datos por su licencia.
 *
 * @param license Licencia del vehículo a eliminar.
 * @throws runtime_error Si hay un error al eliminar el vehículo.
 */
void DataBase::rmVehicle(const string& license) {
    string sqlRmVehicle = "DELETE FROM vehicle WHERE license = '" + license + "';";
    if (sqlite3_exec(db, sqlRmVehicle.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

/**
 * @brief Muestra todos los vehículos de la base de datos.
 *
 * @throws runtime_error Si hay un error al ejecutar la consulta.
 */
void DataBase::showVehicles() {
    if (sqlite3_exec(db, "SELECT * FROM vehicle;", callback, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

/**
 * @brief Muestra un vehículo específico por su licencia.
 *
 * @param license Licencia del vehículo a buscar.
 * @throws runtime_error Si hay un error al ejecutar la consulta.
 */
void DataBase::showVehicleByLicense(const string& license) {
    string sql = "SELECT * FROM vehicle WHERE license = '" + license + "';";

    if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

/**
 * @brief Muestra todos los vehículos de un cliente específico.
 *
 * @param client_id ID del cliente cuyos vehículos se desean mostrar.
 * @throws runtime_error Si hay un error al ejecutar la consulta.
 */
void DataBase::showVehiclesByClientId(int client_id) {
    string sql = "SELECT * FROM vehicle WHERE client_id = " + to_string(client_id) + ";";

    if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

/**
 * @brief Agrega un cliente a la base de datos.
 *
 * También agrega el vehículo asociado al cliente.
 *
 * @param cl Objeto de tipo Client que contiene la información del cliente a agregar.
 * @throws runtime_error Si hay un error al insertar el cliente.
 */
void DataBase::addClient(const Client& cl) {
    string sqlInsert = "INSERT OR IGNORE INTO client (id, balance, name, age, address, email, phone) VALUES ("
        + to_string(cl.getId()) + ", "
        + to_string(cl.getBalance()) + ", '"
        + cl.getName() + "', "
        + to_string(cl.getAge()) + ", '"
        + cl.getAddress() + "', '"
        + cl.getEmail() + "', '"
        + cl.getPhone() + "');";

    if (sqlite3_exec(db, sqlInsert.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }

    addVehicle(cl.getId(), cl.getVehicle());
}


/**
 * @brief Elimina un cliente de la base de datos por su ID.
 *
 * @param id ID del cliente a eliminar.
 * @throws runtime_error Si hay un error al eliminar el cliente.
 */
void DataBase::rmClient(int id) {
    string sqlRmClient = "DELETE FROM client WHERE id = " + to_string(id) + ";";
    if (sqlite3_exec(db, sqlRmClient.c_str(), 0, 0, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

/**
 * @brief Muestra por consola todos los clientes de la base de datos.
 *
 * @throws runtime_error Si hay un error al ejecutar la consulta.
 */
void DataBase::showClients() {
    if (sqlite3_exec(db, "SELECT * FROM client;", callback, nullptr, &errMsg) != SQLITE_OK){
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

/**
 * @brief Muestra por consola un cliente específico por su ID.
 *
 * Llama a un callback para procesar cada fila de resultados.
 *
 * @param id ID del cliente a buscar.
 * @throws runtime_error Si hay un error al ejecutar la consulta.
 */
void DataBase::showClientById(const int id) {
    string sql = "SELECT * FROM client WHERE id = " + to_string(id) + ";";

    if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}

/**
 * @brief Muestra por consola un cliente específico por su nombre.
 *
 * Llama a un callback para procesar cada fila de resultados.
 *
 * @param name Nombre del cliente a buscar.
 * @throws runtime_error Si hay un error al ejecutar la consulta.
 */
void DataBase::showClientByName(const string& name) {
    string sql = "SELECT * FROM client WHERE name = '" + name + "';";

    if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &errMsg) != SQLITE_OK) {
        throw runtime_error(errMsg);
        sqlite3_free(errMsg);
    }
}


/**
 * @brief Callback que se llama para cada fila de resultados de una consulta.
 *
 * @param data Puntero a datos adicionales (no utilizado aquí).
 * @param argc Número de columnas en la fila.
 * @param argv Array de punteros a los valores de las columnas.
 * @param azColName Array de punteros a los nombres de las columnas.
 * @return 0 para continuar.
 */
int DataBase::callback(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << " | ";
    }
    cout << endl;
    return 0;
}

/**
 * @brief Obtiene un cliente de la base de datos por su ID.
 *
 * @param id ID del cliente a buscar.
 * @return Objeto Client con la información del cliente.
 * @throws runtime_error Si hay un error al ejecutar la consulta.
 */
Client DataBase::getClientById(int id) {
    sqlite3_stmt* stmt;
    const char* sqlQuery =
        "SELECT client.id, client.name, client.age, client.address, client.email, client.phone, "
        "vehicle.license, vehicle.type, vehicle.color, vehicle.brand, vehicle.model, "
        "client.balance "
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
        double balance = sqlite3_column_double(stmt, 11);

        client = Client(clientId, name, age, address, email, phone, license, type, color, brand, model);
        client.setBalance(balance);
    }

    sqlite3_finalize(stmt);

    return client;
}

/**
 * @brief Obtiene un cliente de la base de datos por su nombre.
 *
 * @param name Nombre del cliente a buscar.
 * @return Objeto Client con la información del cliente.
 * @throws runtime_error Si hay un error al ejecutar la consulta.
 */
Client DataBase::getClientByName(string name) {
    sqlite3_stmt* stmt;
    const char* sqlQuery =
        "SELECT client.id, client.name, client.age, client.address, client.email, client.phone, "
        "vehicle.license, vehicle.type, vehicle.color, vehicle.brand, vehicle.model, "
        "client.balance "
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
        double balance = sqlite3_column_double(stmt, 11);

        client = Client(clientId, name, age, address, email, phone, license, type, color, brand, model);
        client.setBalance(balance);
    }

    sqlite3_finalize(stmt);

    return client;
}

void DataBase::updateBalance(int id, double balance){
    sqlite3_stmt* stmt;
    const char* sqlQuery = "UPDATE client SET balance = ? WHERE id = ?";

    if (sqlite3_prepare_v2(db, sqlQuery, -1, &stmt, nullptr) != SQLITE_OK) {
        throw runtime_error(sqlite3_errmsg(db));
    }

    sqlite3_bind_double(stmt, 1, balance);
    sqlite3_bind_int(stmt, 2, id);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

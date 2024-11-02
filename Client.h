#ifndef CLIENT_H
#define CLIENT_H

#include "Person.h"
#include "Vehicle.h"
#include <vector>

#define NULLCLIENT Client()

/**
 * @brief Clase para administrar los datos de un cliente
 */
class Client : public Person {

friend std::ostream& operator<<(std::ostream& os, const Client& Client);

private:
    unsigned long long id; /**<ID relacionado a la tarjeta RFID unica de cada cliente*/
    std::vector<Vehicle> vehicleVector; /**<Vector que almacena objetos con los datos del vehiculo*/
    double balance; /**<Lleva el saldo del cliente, en pesos argentinos*/

public:
    Client( unsigned long long id = 0, const std::string& name ="", unsigned int age = 0, unsigned int dni = 0,
            const std::string& address ="", const std::string& email = "", const std::string& phone = "",
            const std::string& license = "", const std::string& type = "", const std::string& color = "",
            const std::string& brand = "", const std::string& model = "");

    unsigned long long getId() const;
    double getBalance() const;
    std::vector<Vehicle> getVehicles() const;

    void setId(unsigned long long id);
    void addVehicle(const Vehicle& vehicle);
    void removeVehicleByPos(int vehiclePos);
    void removeVehicleByLicense(std::string license);
    void setBalance(double balance);
    inline bool isNull() {return id ? false : true;}
};

#endif

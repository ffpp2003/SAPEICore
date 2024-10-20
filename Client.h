#ifndef CLIENT_H
#define CLIENT_H

#include "Person.h"
#include "Vehicle.h"

/**
 * @brief Clase para administrar los datos de un cliente
 */
class Client : public Person {

friend std::ostream& operator<<(std::ostream& os, const Client& Client);

private:
    int id; /**<ID relacionado a la tarjeta RFID unica de cada cliente*/
    Vehicle vehicle; /**<Objeto que almacena los datos del vehiculo*/
    float balance; /**<Lleva el saldo del cliente, en pesos argentinos*/

public:
    Client( int id = 0, const std::string& name ="", int age = 0, const std::string& address ="", const std::string& email = "",
            const std::string& phone = "", const std::string& license = "", const std::string& type = "",
            const std::string& color = "", const std::string& brand = "", const std::string& model = "");

    int getId() const;
    int getBalance() const;

    void setId(int id);
    void setVehicle(const Vehicle& vehicle);
    void setBalance(float balance);
};

#endif

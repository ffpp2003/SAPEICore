#ifndef CLIENT_H
#define CLIENT_H

#include "Person.h"
#include "Vehicle.h"

class Client : public Person {

friend std::ostream& operator<<(std::ostream& os, const Client& Client);

private:
    int id;
    Vehicle vehicle;
    float balance;

public:
    Client( int id, const std::string& name, int age, const std::string& address, const std::string& email, const std::string& phone,
        const std::string& license, const std::string& type, const std::string& color, const std::string& brand, const std::string& model);

    int getClientID() const;

    void setClientID(int id);
    void setVehicle(const Vehicle& vehicle);
};

#endif

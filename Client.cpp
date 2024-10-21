#include "Client.h"

Client::Client(int id, const std::string& name, int age,
                const std::string& address,
                const std::string& email, const std::string& phone,
                const std::string& license, const std::string& type,
                const std::string& color, const std::string& brand,
                const std::string& model)
    : Person(name, age, address, email, phone), id(id), vehicle(license, type, color, brand, model) {
    balance = 0;
}

int Client::getId() const {
    return id;
}

int Client::getBalance() const {
    return balance;
}

Vehicle Client::getVehicle() const{
  return vehicle;
}

void Client::setId(int id) {
    this->id= id;
}

void Client::setVehicle(const Vehicle& vehicle) {
    this->vehicle = vehicle;
}

void Client::setBalance(float balance){
    this->balance = balance;
}

std::ostream& operator<<(std::ostream& os, const Client& client) {
    os << static_cast<const Person&>(client)
    << "ID: " << client.id << std::endl
    << "Saldo: " << client.balance << std::endl
    << "Vehiculo:" << std::endl 
    << client.vehicle << std::endl;
    return os;
}

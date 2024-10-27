#include "Client.h"
#include "Vehicle.h"

Client::Client(unsigned long long id, const std::string& name, int age,
                const std::string& address,
                const std::string& email, const std::string& phone,
                const std::string& license, const std::string& type,
                const std::string& color, const std::string& brand,
                const std::string& model)
    : Person(name, age, address, email, phone), id(id){
    balance = 0;
    if(license != ""){
      Vehicle firstVehicle(license, type, color, brand, model);
      vehicleVector.push_back(firstVehicle);
    }
}

unsigned long long Client::getId() const {
    return id;
}

double Client::getBalance() const {
    return balance;
}

std::vector<Vehicle> Client::getVehicles() const{
  return vehicleVector;
}

void Client::setId(unsigned long long id) {
    this->id= id;
}

void Client::addVehicle(const Vehicle& vehicle) {
    vehicleVector.push_back(vehicle);
}

void Client::removeVehicleByPos(int vehiclePos){
  if(vehiclePos > 0 && vehiclePos <= vehicleVector.size())
    vehicleVector.erase(vehicleVector.begin() + vehiclePos-1);
}

void Client::removeVehicleByLicense(std::string license){
  for(int i = 0; i < vehicleVector.size(); i++)
    if(vehicleVector[i].getLicensePlate() == license)
      vehicleVector.erase(vehicleVector.begin() + i);
}

void Client::setBalance(double balance){
    this->balance = balance;
}

std::ostream& operator<<(std::ostream& os, const Client& client) {
    os << static_cast<const Person&>(client)
    << "ID: " << client.id << std::endl
    << "Saldo: " << client.balance << std::endl;
    for(int i = 0; i < client.vehicleVector.size(); i++){
      os << "Vehiculo N: " << i+1 << std::endl
      << client.vehicleVector.at(i) << std::endl;
    }

    return os;
}

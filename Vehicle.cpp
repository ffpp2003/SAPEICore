#include "Vehicle.h"

using namespace std;

Vehicle::Vehicle(const std::string& license, const std::string& type, const std::string& color, const std::string& brand, const std::string& model, unsigned long long clientId)
    : licensePlate(license), type(type), color(color), brand(brand), model(model), clientId(clientId){
}

std::string Vehicle::getLicensePlate() const {
  return licensePlate; 
}
std::string Vehicle::getType() const {
  return type;
}

std::string Vehicle::getColor() const {
  return color;
}

std::string Vehicle::getBrand() const {
  return brand;
}

std::string Vehicle::getModel() const {
  return model;
}

unsigned long long Vehicle::getClientId() const {
  return clientId;
}

void Vehicle::setLicensePlate(const std::string& license) {
  this->licensePlate = license;
}

void Vehicle::setType(const std::string& type) {
  this->type = type;
}

void Vehicle::setColor(const std::string& color) {
  this->color = color;
}

void Vehicle::setBrand(const std::string& brand) {
  this->brand = brand;
}

void Vehicle::setModel(const std::string& model) {
  this->model = model;
}

void Vehicle::setClientId(unsigned long long clientId) {
  if (this->clientId == 0)
    this->clientId = clientId;
  else
    cerr << getErrMsg(VH_CLIENT_ASSOCIATE) << endl;
}

void Vehicle::updateClientId(unsigned long long clientId) {
    this->clientId = clientId;
}

std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle) {
    os << "Patente: " << vehicle.licensePlate << std::endl
       << "Tipo: " << vehicle.type << std::endl
       << "Color: " << vehicle.color << std::endl
       << "Marca: " << vehicle.brand << std::endl
       << "Modelo: " << vehicle.model;
    return os;
}

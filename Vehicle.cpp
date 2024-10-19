#include "Vehicle.h"

Vehicle::Vehicle(const std::string& license, const std::string& type, const std::string& color, const std::string& brand, const std::string& model)
    : licensePlate(license), type(type), color(color), brand(brand), model(model) {
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

std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle) {
    os << "Patente: " << vehicle.licensePlate << std::endl
       << "Tipo: " << vehicle.type << std::endl
       << "Color: " << vehicle.color << std::endl
       << "Marca: " << vehicle.brand << std::endl
       << "Modelo: " << vehicle.model;
    return os;
}

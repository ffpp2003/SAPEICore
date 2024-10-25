#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>

class Vehicle {

friend std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle);

private:
    std::string licensePlate;
    std::string type;
    std::string color;
    std::string brand;
    std::string model;

public:
    Vehicle();
    Vehicle(const std::string& license = "", const std::string& type = "", const std::string& color = "", const std::string& brand = "", const std::string& model = "");

    std::string getLicensePlate() const;
    std::string getType() const;
    std::string getColor() const;
    std::string getBrand() const;
    std::string getModel() const;

    void setLicensePlate(const std::string& license);
    void setType(const std::string& type);
    void setColor(const std::string& color);
    void setBrand(const std::string& brand);
    void setModel(const std::string& model);

};

#endif

#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>
#include "Error.h"

#define NULLVEHICLE Vehicle()

class Vehicle {

friend std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle);
friend class Client;

private:
    std::string licensePlate;
    std::string type;
    std::string color;
    std::string brand;
    std::string model;
    unsigned long long clientId;
    void updateClientId(unsigned long long id);

public:
    Vehicle(const std::string& license = "", const std::string& type = "", const std::string& color = "", const std::string& brand = "",
            const std::string& model = "", unsigned long long clientId = 0);

    std::string getLicensePlate() const;
    std::string getType() const;
    std::string getColor() const;
    std::string getBrand() const;
    std::string getModel() const;
    unsigned long long getClientId() const;

    void setLicensePlate(const std::string& license);
    void setType(const std::string& type);
    void setColor(const std::string& color);
    void setBrand(const std::string& brand);
    void setModel(const std::string& model);
    void setClientId(unsigned long long id);
    inline bool isNull() const { return licensePlate.empty(); }

};

#endif

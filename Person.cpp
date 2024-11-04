#include "Person.h"


using namespace std;

Person::Person(const string& name, unsigned int age, unsigned int dni, const string& address, const string& email, const std::string& phone)
    : name(name), age(age), dni(dni), address(address), email(email), phone(phone){}

string Person::getName() const {
    return name;
}

unsigned int Person::getAge() const {
    return age;
}

unsigned int Person::getDni() const{
    return dni;
}

string Person::getAddress() const {
    return address;
}

string Person::getEmail() const {
    return email;
}

string Person::getPhone() const {
    return phone;
}

void Person::setName(const std::string& name){
    this->name = name;
}

void Person::setAge(const unsigned int age){
    this->age = age;
}

void Person::setDni(const unsigned int dni){
    this->dni = dni;
}

void Person::setAddress(const std::string& address){
    this->address = address;
}

void Person::setEmail(const std::string& email){
    this->email = email;
}

void Person::setPhone(const std::string& phone){
    this->phone = phone;
}

std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << "Nombre: " << person.name << std::endl;
    os << "Edad: " << person.age << std::endl;
    os << "DNI: " << person.dni << std::endl;
    os << "Dirección: " << person.address << std::endl;
    os << "email: " << person.email << std::endl;
    os << "telefono: " << person.phone << std::endl;
    return os;
}

#include "Person.h"

Person::Person(const std::string& name, int age, unsigned int dni, const std::string& address, const std::string& email, const std::string& phone)
    : name(name), age(age), dni(dni), address(address), email(email), phone(phone){}

std::string Person::getName() const {
    return name;
}

int Person::getAge() const {
    return age;
}

unsigned int Person::getDni() const {
	return dni;
}

std::string Person::getAddress() const {
    return address;
}

std::string Person::getEmail() const {
    return email;
}

std::string Person::getPhone() const {
    return phone;
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

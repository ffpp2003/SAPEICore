#include "Person.h"

using namespace std;

Person::Person(const string& name, int age, unsigned int dni, const string& address, const string& email, const std::string& phone)
    : name(name), age(age), address(address), email(email), phone(phone){}

string Person::getName() const {
    return name;
}

int Person::getAge() const {
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

ostream& operator<<(std::ostream& os, const Person& person) {
    os << "Nombre: " << person.name << endl;
    os << "Edad: " << person.age << endl;
    os << "DNI: " << person.dni << endl;
    os << "Dirección: " << person.address << endl;
    os << "email: " << person.email << endl;
    os << "telefono: " << person.phone << endl;
    return os;
}

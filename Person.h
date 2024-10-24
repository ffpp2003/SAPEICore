#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

class Person {

friend std::ostream& operator<<(std::ostream& os, const Person& person);

private:
    std::string name;
    int age;
    unsigned int dni;
    std::string address;
    std::string email;
    std::string phone;

public:
    Person(const std::string& name = "", int age = 0,unsigned int dni = 0, const std::string& address = "", const std::string& email = "", const std::string& phone = "");

    std::string getName() const;
    int getAge() const;
    unsigned int getDni() const;
    std::string getAddress() const;
    std::string getEmail() const;
    std::string getPhone() const;

};

#endif // PERSON_H

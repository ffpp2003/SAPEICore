#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

class Person {

friend std::ostream& operator<<(std::ostream& os, const Person& person);

private:
    std::string name;
    unsigned int age;
    unsigned int dni;
    std::string address;
    std::string email;
    std::string phone;

public:
    Person(const std::string& name = "", unsigned int age = 0, unsigned int dni = 0, const std::string& address = "",
            const std::string& email = "", const std::string& phone = "");

    std::string getName() const;
    unsigned int getAge() const;
    unsigned int getDni() const;
    std::string getAddress() const;
    std::string getEmail() const;
    std::string getPhone() const;

    void setName(const std::string&);
    void setAge(const unsigned int);
    void setDni(const unsigned int);
    void setAddress(const std::string&);
    void setEmail(const std::string&);
    void setPhone(const std::string&);
};

#endif // PERSON_H

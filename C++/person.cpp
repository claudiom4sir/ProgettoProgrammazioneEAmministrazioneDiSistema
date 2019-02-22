#include "person.h"
#include <algorithm>
#include <ostream>
#include <string>

void Person::swap(Person& other)  {
    std::swap(_name, other._name);
    std::swap(_surname, other._surname);
    std::swap(_age, other._age);
}

Person::Person() : _name(""), _surname(""), _age(0) {}

Person::Person(const std::string& name, const std::string& surname, unsigned int age) 
    : _name(name), _surname(surname), _age(age) {}

Person::Person(const Person& other) 
    : _name(other._name), _surname(other._surname), _age(other._age) {}

Person::~Person() {}

Person& Person::operator=(const Person& other) {
    if(this != &other){
        Person p(other);
        swap(p);
    }
    return *this;
}

bool Person::operator==(const Person& other) const {
    return _name.compare(other._name) == 0 && _surname.compare(other._surname) == 0 && _age == other._age; 
}

std::ostream& operator<<(std::ostream& os, const Person& p){
    os << "[" << p._name << " " << p._surname << " " << p._age << "]";
    return os;
}

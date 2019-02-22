#ifndef Person_H
#define Person_H
#include <string>

/**
 * @file person.h
 * @brief Declaration of the struct Person.
**/

/**
 * @brief Person struct used for testing MySet class
 * 
 * This struct represents a person.
 * It has fundamental methods and an operator== that allows to check if two Person are equals or not.
**/
struct Person {

    std::string _name;
    std::string _surname;
    unsigned int _age;

    void swap(Person& other);
    Person();

    Person(const std::string& name, const std::string& surname, unsigned int age);

    Person(const Person& other);

    ~Person();

    Person& operator=(const Person& other);

    /**
     * @brief Equal operator
     * 
     * @param other Const reference to a Person.
     * @return True if the current Person has name, surname and age equals to the other Person passed as parameter.
    **/
    bool operator==(const Person& other) const;

};

std::ostream& operator<<(std::ostream& os, const Person& p);

#endif
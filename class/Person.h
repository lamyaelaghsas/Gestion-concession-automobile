#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

using namespace std;

namespace carconfig {

class Person
{
    friend ostream& operator<<(ostream& s, const Person& p);
    friend istream& operator>>(istream& s, Person& p);
    
protected:
    string lastName;   // Nom
    string firstName;  // Prénom
    
public:
    // Constructeurs
    Person();
    Person(const string& lastName, const string& firstName);
    Person(const Person& p);
    
    // Destructeur
    virtual ~Person();
    
    // Setters
    void setLastName(const string& lastName);
    void setFirstName(const string& firstName);
    
    // Getters
    string getLastName() const;
    string getFirstName() const;
    
    // Opérateurs
    Person& operator=(const Person& p);
    int operator<(const Person& p) const;
    int operator>(const Person& p) const;
    int operator==(const Person& p) const;
    
    // Affichage
    void display() const;
    
private:
    int compare(const Person& p) const;
};

} // namespace carconfig

#endif
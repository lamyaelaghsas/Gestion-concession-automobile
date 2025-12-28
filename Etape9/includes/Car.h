#ifndef CAR_H
#define CAR_H

#include "Model.h"
#include "Option.h"
#include <string>
#include <iostream>

using namespace std;

namespace carconfig {

class Car
{
    friend ostream& operator<<(ostream& s, const Car& car);
    friend istream& operator>>(istream& s, Car& car);
    friend Car operator+(const Option& opt, const Car& car);
    
private:
    string name;
    Model model;
    Option* options[5];
    
    int comparePrice(const Car& car) const;
    
public:
    Car();
    Car(const string& n, const Model& m);
    Car(const Car& car);
    ~Car();
    
    string getName() const;
    Model getModel() const;
    float getPrice() const;
    
    void setName(const string& n);
    void setModel(const Model& m);
    
    void addOption(const Option& option);
    void removeOption(string code);
    
    void display() const;
    string toString() const;
    
    // OPÉRATEURS
    Car& operator=(const Car& car);
    Car operator+(const Option& opt) const;
    Car operator-(const Option& opt) const;
    Car operator-(const string& code) const;
    int operator<(const Car& car) const;
    int operator>(const Car& car) const;
    int operator==(const Car& car) const;
    Option* operator[](int index) const;
};

} // namespace carconfig

#endif
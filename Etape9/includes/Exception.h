#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <iostream>

using namespace std;

namespace carconfig {

class Exception
{
protected:
    string message;
    
public:
    // Constructeurs
    Exception();
    Exception(const string& message);
    Exception(const Exception& e);
    
    // Destructeur
    virtual ~Exception();
    
    // Setters
    void setMessage(const string& message);
    
    // Getters
    string getMessage() const;
    
    // Opérateurs
    Exception& operator=(const Exception& e);
    
    // Affichage
    void display() const;
};

} // namespace carconfig

#endif
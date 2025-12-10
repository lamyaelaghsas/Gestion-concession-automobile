#ifndef PASSWORDEXCEPTION_H
#define PASSWORDEXCEPTION_H

#include "Exception.h"
#include <string>

using namespace std;

namespace carconfig {

class PasswordException : public Exception
{
private:
    int code;
    
public:
    // Constantes statiques pour les codes d'erreur
    static const int INVALID_LENGTH = 1;
    static const int ALPHA_MISSING = 2;
    static const int DIGIT_MISSING = 3;
    static const int NO_PASSWORD = 4;
    
    // Constructeurs
    PasswordException();
    PasswordException(const string& message, int code);
    PasswordException(const PasswordException& e);
    
    // Destructeur
    virtual ~PasswordException();
    
    // Setters
    void setCode(int code);
    
    // Getters
    int getCode() const;
    
    // Opérateurs
    PasswordException& operator=(const PasswordException& e);
};

} // namespace carconfig

#endif
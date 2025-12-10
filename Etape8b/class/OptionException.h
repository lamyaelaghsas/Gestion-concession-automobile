#ifndef OPTIONEXCEPTION_H
#define OPTIONEXCEPTION_H

#include "Exception.h"
#include <string>

using namespace std;

namespace carconfig {

class OptionException : public Exception
{
public:
    // Constructeurs
    OptionException();
    OptionException(const string& message);
    OptionException(const OptionException& e);
    
    // Destructeur
    virtual ~OptionException();
    
    // Opérateurs
    OptionException& operator=(const OptionException& e);
};

} // namespace carconfig

#endif
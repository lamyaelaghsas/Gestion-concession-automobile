#include "OptionException.h"

using namespace std;

namespace carconfig {

//=============================================================================
// CONSTRUCTEURS
//=============================================================================

OptionException::OptionException() : Exception()
{
    cout << "OptionException: Constructeur par defaut" << endl;
}

OptionException::OptionException(const string& message) : Exception(message)
{
    cout << "OptionException: Constructeur d'initialisation" << endl;
}

OptionException::OptionException(const OptionException& e) : Exception(e)
{
    cout << "OptionException: Constructeur de copie" << endl;
}

//=============================================================================
// DESTRUCTEUR
//=============================================================================

OptionException::~OptionException()
{
    cout << "OptionException: Destructeur" << endl;
}

//=============================================================================
// OPÉRATEURS
//=============================================================================

OptionException& OptionException::operator=(const OptionException& e)
{
    Exception::operator=(e);
    return (*this);
}

} // namespace carconfig
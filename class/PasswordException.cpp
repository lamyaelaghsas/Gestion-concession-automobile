#include "PasswordException.h"

using namespace std;

namespace carconfig {

//=============================================================================
// CONSTRUCTEURS
//=============================================================================

PasswordException::PasswordException() : Exception("Constructeur par defaut PasswordException")
{
    cout << "PasswordException: Constructeur par defaut" << endl;
    setCode(0);
}

PasswordException::PasswordException(const string& message, int code) : Exception(message)
{
    cout << "PasswordException: Constructeur d'initialisation" << endl;
    setCode(code);
}

PasswordException::PasswordException(const PasswordException& e) : Exception(e)
{
    cout << "PasswordException: Constructeur de copie" << endl;
    setCode(e.getCode());
}

//=============================================================================
// DESTRUCTEUR
//=============================================================================

PasswordException::~PasswordException()
{
    cout << "PasswordException: Destructeur" << endl;
}

//=============================================================================
// SETTERS
//=============================================================================

void PasswordException::setCode(int code)
{
    this->code = code;
}

//=============================================================================
// GETTERS
//=============================================================================

int PasswordException::getCode() const
{
    return code;
}

//=============================================================================
// OPÉRATEURS
//=============================================================================

PasswordException& PasswordException::operator=(const PasswordException& e)
{
    Exception::operator=(e);
    setCode(e.getCode());
    return (*this);
}

} // namespace carconfig
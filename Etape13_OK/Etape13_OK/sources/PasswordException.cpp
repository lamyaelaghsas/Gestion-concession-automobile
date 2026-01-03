#include "../includes/PasswordException.h"

using namespace std;

namespace carconfig {

//=============================================================================
// CONSTRUCTEURS
//=============================================================================

PasswordException::PasswordException() : Exception("Constructeur par defaut PasswordException")
{
    setCode(0);
}

PasswordException::PasswordException(const string& message, int code) : Exception(message)
{
    setCode(code);
}

PasswordException::PasswordException(const PasswordException& e) : Exception(e)
{
    setCode(e.getCode());
}

//=============================================================================
// DESTRUCTEUR
//=============================================================================

PasswordException::~PasswordException()
{
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
#include "../includes/OptionException.h"

using namespace std;

namespace carconfig {

//=============================================================================
// CONSTRUCTEURS
//=============================================================================

OptionException::OptionException() : Exception()
{
}

OptionException::OptionException(const string& message) : Exception(message)
{
}

OptionException::OptionException(const OptionException& e) : Exception(e)
{
}

//=============================================================================
// DESTRUCTEUR
//=============================================================================

OptionException::~OptionException()
{
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
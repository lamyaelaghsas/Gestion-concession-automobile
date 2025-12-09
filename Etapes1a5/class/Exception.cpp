#include "Exception.h"

using namespace std;

namespace carconfig {

//=============================================================================
// CONSTRUCTEURS
//=============================================================================

Exception::Exception()
{
    setMessage("Defaut Message");
}

Exception::Exception(const string& message)
{
    setMessage(message);
}

Exception::Exception(const Exception& e)
{
    setMessage(e.getMessage());
}

//=============================================================================
// DESTRUCTEUR
//=============================================================================

Exception::~Exception()
{
}

//=============================================================================
// SETTERS
//=============================================================================

void Exception::setMessage(const string& message)
{
    this->message = message;
}

//=============================================================================
// GETTERS
//=============================================================================

string Exception::getMessage() const
{
    return message;
}

//=============================================================================
// OPÉRATEURS
//=============================================================================

Exception& Exception::operator=(const Exception& e)
{
    setMessage(e.getMessage());
    return (*this);
}

//=============================================================================
// AFFICHAGE
//=============================================================================

void Exception::display() const
{
    cout << "Erreur: " << endl;
    cout << getMessage() << endl;
}

} // namespace carconfig
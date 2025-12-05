#include "Exception.h"

using namespace std;

namespace carconfig {

//=============================================================================
// CONSTRUCTEURS
//=============================================================================

Exception::Exception()
{
    cout << "Exception: Constructeur par defaut" << endl;
    setMessage("Defaut Message");
}

Exception::Exception(const string& message)
{
    cout << "Exception: Constructeur d'initialisation" << endl;
    setMessage(message);
}

Exception::Exception(const Exception& e)
{
    cout << "Exception: Constructeur de copie" << endl;
    setMessage(e.getMessage());
}

//=============================================================================
// DESTRUCTEUR
//=============================================================================

Exception::~Exception()
{
    cout << "Exception: Destructeur" << endl;
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
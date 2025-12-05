#include "Client.h"
#include <iostream>

using namespace std;

namespace carconfig {

//=============================================================================
// CONSTRUCTEURS
//=============================================================================

Client::Client() : Actor()
{
    cout << "Client: Constructeur par defaut" << endl;
    setGsm("0000/00.00.00");
}

Client::Client(const string& lastName, const string& firstName, int id, const string& gsm)
    : Actor(lastName, firstName, id)
{
    cout << "Client: Constructeur d'initialisation" << endl;
    setGsm(gsm);
}

Client::Client(const Client& c) : Actor(c)
{
    cout << "Client: Constructeur de copie" << endl;
    setGsm(c.getGsm());
}

//=============================================================================
// DESTRUCTEUR
//=============================================================================

Client::~Client()
{
    cout << "Client: Destructeur" << endl;
}

//=============================================================================
// SETTERS
//=============================================================================

void Client::setGsm(const string& gsm)
{
    this->gsm = gsm;
}

//=============================================================================
// GETTERS
//=============================================================================

string Client::getGsm() const
{
    return gsm;
}

//=============================================================================
// AFFICHAGE
//=============================================================================

void Client::display() const
{
    cout << "CLIENT:" << endl;
    cout << "Nom: " << getLastName() << endl;
    cout << "Prenom: " << getFirstName() << endl;
    cout << "ID: " << getId() << endl;
    cout << "GSM: " << getGsm() << endl;
}

//=============================================================================
// OPÉRATEURS
//=============================================================================

Client& Client::operator=(const Client& c)
{
    Actor::operator=(c);
    setGsm(c.getGsm());
    return (*this);
}

ostream& operator<<(ostream& s, const Client& c)
{
    s << "CLIENT:" << endl;
    s << "Nom: " << c.getLastName() << endl;
    s << "Prenom: " << c.getFirstName() << endl;
    s << "ID: " << c.getId() << endl;
    s << "GSM: " << c.getGsm() << endl;
    return s;
}

//=============================================================================
// MÉTHODES VIRTUELLES
//=============================================================================

string Client::tuple() const
{
    string str;
    str = to_string(getId()) + ";" + getLastName() + ";" + 
          getFirstName() + ";" + getGsm();
    return str;
}

string Client::toString() const
{
    string str;
    str = "[C" + to_string(getId()) + "] " + getLastName() + " " + getFirstName();
    return str;
}

} // namespace carconfig
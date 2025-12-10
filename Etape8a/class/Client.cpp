#include "Client.h"
#include <iostream>

using namespace std;

namespace carconfig {

//=============================================================================
// CONSTRUCTEURS
//=============================================================================

Client::Client() : Actor()
{
    setGsm("0000/00.00.00");
}

Client::Client(const string& lastName, const string& firstName, int id, const string& gsm)
    : Actor(lastName, firstName, id)
{
    setGsm(gsm);
}

Client::Client(const Client& c) : Actor(c)
{
    setGsm(c.getGsm());
}

//=============================================================================
// DESTRUCTEUR
//=============================================================================

Client::~Client()
{
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
    s << "<Client>" << endl;
    s << "<lastName>" << endl;
    s << c.getLastName() << endl;
    s << "</lastName>" << endl;
    s << "<firstName>" << endl;
    s << c.getFirstName() << endl;
    s << "</firstName>" << endl;
    s << "<id>" << endl;
    s << c.getId() << endl;
    s << "</id>" << endl;
    s << "<gsm>" << endl;
    s << c.getGsm() << endl;
    s << "</gsm>" << endl;
    s << "</Client>" << endl;
    
    return s;
}

istream& operator>>(istream& s, Client& c)
{
    string line;
    
    // Lire <Client>
    getline(s, line);
    
    // Lire <lastName>
    getline(s, line);
    
    // Lire la valeur du lastName
    getline(s, line);
    c.setLastName(line);
    
    // Lire </lastName>
    getline(s, line);
    
    // Lire <firstName>
    getline(s, line);
    
    // Lire la valeur du firstName
    getline(s, line);
    c.setFirstName(line);
    
    // Lire </firstName>
    getline(s, line);
    
    // Lire <id>
    getline(s, line);
    
    // Lire la valeur de l'id
    getline(s, line);
    c.setId(stoi(line));
    
    // Lire </id>
    getline(s, line);
    
    // Lire <gsm>
    getline(s, line);
    
    // Lire la valeur du gsm
    getline(s, line);
    c.setGsm(line);
    
    // Lire </gsm>
    getline(s, line);
    
    // Lire </Client>
    getline(s, line);
    
    return s;
}

// Opérateur de comparaison pour set<Client> (tri alphabétique par nom)
bool Client::operator<(const Client& c) const {
    return getLastName() < c.getLastName();
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
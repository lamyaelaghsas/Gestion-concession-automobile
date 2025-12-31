#include "../includes/Person.h"
#include <iostream>

using namespace std;

namespace carconfig {

//=============================================================================
// CONSTRUCTEURS
//=============================================================================

Person::Person()
{
    setLastName("NomPersonne");
    setFirstName("PrenomPersonne");
}

Person::Person(const string& lastName, const string& firstName)
{
    setLastName(lastName);
    setFirstName(firstName);
}

Person::Person(const Person& p)
{
    setLastName(p.getLastName());
    setFirstName(p.getFirstName());
}

//=============================================================================
// DESTRUCTEUR
//=============================================================================

Person::~Person()
{
}

//=============================================================================
// SETTERS
//=============================================================================

void Person::setLastName(const string& lastName)
{
    this->lastName = lastName;
}

void Person::setFirstName(const string& firstName)
{
    this->firstName = firstName;
}

//=============================================================================
// GETTERS
//=============================================================================

string Person::getLastName() const
{
    return lastName;
}

string Person::getFirstName() const
{
    return firstName;
}

//=============================================================================
// AFFICHAGE
//=============================================================================

void Person::display() const
{
    cout << "PERSONNE:" << endl;
    cout << "Nom: " << getLastName() << endl;
    cout << "Prenom: " << getFirstName() << endl;
}

//=============================================================================
// OPÉRATEURS
//=============================================================================

Person& Person::operator=(const Person& p)
{
    setLastName(p.getLastName());
    setFirstName(p.getFirstName());
    return (*this);
}

int Person::operator<(const Person& p) const
{
    return compare(p) == -1;
}

int Person::operator>(const Person& p) const
{
    return compare(p) == 1;
}

int Person::operator==(const Person& p) const
{
    return compare(p) == 0;
}

ostream& operator<<(ostream& s, const Person& p)
{
    s << "PERSONNE:" << endl;
    s << "Nom: " << p.getLastName() << endl;
    s << "Prenom: " << p.getFirstName() << endl;
    return s;
}

istream& operator>>(istream& s, Person& p)
{
    string nom, prenom;
    
    cout << "Encoder le nom : ";
    getline(s >> ws, nom);
    
    cout << "Encoder le prenom : ";
    getline(s >> ws, prenom);
    
    p.setLastName(nom);
    p.setFirstName(prenom);
    
    return s;
}

//=============================================================================
// MÉTHODE AUXILIAIRE PRIVÉE
//=============================================================================

int Person::compare(const Person& p) const
{
    // Compare d'abord les noms
    if (getLastName()[0] == p.getLastName()[0])
    {
        // Si les noms sont égaux, compare les prénoms
        if (getFirstName()[0] > p.getFirstName()[0]) return 1;
        if (getFirstName()[0] < p.getFirstName()[0]) return -1;
        return 0;
    }
    else
    {
        if (getLastName()[0] > p.getLastName()[0]) return 1;
        if (getLastName()[0] < p.getLastName()[0]) return -1;
        return 0;
    }
}

} // namespace carconfig
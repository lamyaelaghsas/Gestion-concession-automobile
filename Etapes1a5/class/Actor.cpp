#include "Actor.h"
#include <iostream>

using namespace std;

namespace carconfig {

// Initialisation du compteur statique
int Actor::currentNumber = 0;

//=============================================================================
// CONSTRUCTEURS
//=============================================================================

Actor::Actor() : Person()
{
    cout << "Actor: Constructeur par defaut" << endl;
    setId(0);
}

Actor::Actor(const string& lastName, const string& firstName, int id) : Person(lastName, firstName)
{
    cout << "Actor: Constructeur d'initialisation" << endl;
    setId(id);
}

Actor::Actor(const Actor& a) : Person(a)
{
    cout << "Actor: Constructeur de copie" << endl;
    setId(a.getId());
}

//=============================================================================
// DESTRUCTEUR
//=============================================================================

Actor::~Actor()
{
    cout << "Actor: Destructeur" << endl;
}

//=============================================================================
// SETTERS
//=============================================================================

void Actor::setId(int id)
{
    this->id = id;
}

//=============================================================================
// GETTERS
//=============================================================================

int Actor::getId() const
{
    return id;
}

//=============================================================================
// OPÉRATEUR
//=============================================================================

Actor& Actor::operator=(const Actor& a)
{
    Person::operator=(a);
    setId(a.getId());
    return (*this);
}

} // namespace carconfig
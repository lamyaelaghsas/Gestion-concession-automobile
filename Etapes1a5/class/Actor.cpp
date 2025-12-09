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
    setId(0);
}

Actor::Actor(const string& lastName, const string& firstName, int id) : Person(lastName, firstName)
{
    setId(id);
}

Actor::Actor(const Actor& a) : Person(a)
{
    setId(a.getId());
}

//=============================================================================
// DESTRUCTEUR
//=============================================================================

Actor::~Actor()
{
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
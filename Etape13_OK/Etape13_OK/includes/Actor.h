#ifndef ACTOR_H
#define ACTOR_H

#include "Person.h"
#include <string>

using namespace std;

namespace carconfig {

class Actor : public Person
{
protected:
    int id;  // Identifiant unique
    
    
public:

    static int currentNumber;  // Compteur pour générer des IDs uniques

    // Constructeurs
    Actor();
    Actor(const string& lastName, const string& firstName, int id);
    Actor(const Actor& a);
    
    // Destructeur
    virtual ~Actor();
    
    // Setters
    void setId(int id);
    
    // Getters
    int getId() const;
    
    // Opérateur
    Actor& operator=(const Actor& a);
    
    // Méthodes virtuelles pures (classe abstraite)
    virtual string tuple() const = 0;
    virtual string toString() const = 0;
};

} // namespace carconfig

#endif
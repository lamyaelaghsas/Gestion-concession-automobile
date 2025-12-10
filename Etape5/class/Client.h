#ifndef CLIENT_H
#define CLIENT_H

#include "Actor.h"
#include <string>

using namespace std;

namespace carconfig {

class Client : public Actor
{
    friend ostream& operator<<(ostream& s, const Client& c);
    
private:
    string gsm;  // Numéro de téléphone
    
public:
    // Constructeurs
    Client();
    Client(const string& lastName, const string& firstName, int id, const string& gsm);
    Client(const Client& c);
    
    // Destructeur
    virtual ~Client();
    
    // Setters
    void setGsm(const string& gsm);
    
    // Getters
    string getGsm() const;
    
    // Opérateurs
    Client& operator=(const Client& c);
    
    // Affichage
    void display() const;
    
    // Méthodes virtuelles (implémentation des méthodes pures d'Actor)
    virtual string tuple() const;
    virtual string toString() const;
};

} // namespace carconfig

#endif
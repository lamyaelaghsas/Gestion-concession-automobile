#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Actor.h"
#include <string>

using namespace std;

namespace carconfig {

class Employee : public Actor
{
    friend ostream& operator<<(ostream& s, const Employee& e);
    friend istream& operator>>(istream& s, Employee& e); 
    
private:
    string login;
    string* password;  // Pointeur car peut être NULL
    string role;       // "Seller" ou "Administrator"
    
public:
    // Constantes statiques pour les rôles
    static const string ADMINISTRATIVE;
    static const string SELLER;
    
    // Constructeurs
    Employee();
    Employee(const string& lastName, const string& firstName, int id, 
             const string& login, const string& role);
    Employee(const Employee& e);
    
    // Destructeur
    virtual ~Employee();
    
    // Setters
    void setLogin(const string& login);
    void setPassword(const string& password);
    void setRole(const string& role);
    
    // Getters
    string getLogin() const;
    string getPassword() const;
    string getRole() const;
    
    // Opérateurs
    Employee& operator=(const Employee& e);
    bool operator<(const Employee& e) const;  // Pour set<Employee> - tri alphabétique
    
    // Affichage
    void display() const;
    
    // Méthodes virtuelles (implémentation des méthodes pures d'Actor)
    virtual string tuple() const;
    virtual string toString() const;
    
    // Méthode spécifique
    void resetPassword();
};

} // namespace carconfig

#endif // EMPLOYEE_H
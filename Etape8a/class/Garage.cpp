#include "Garage.h"
#include <iostream>
#include <algorithm>

using namespace std;

namespace carconfig {

//=============================================================================
// MÉTHODES POUR LES MODÈLES
//=============================================================================

void Garage::addModel(const Model& m) {
    models.push_back(m);
}

void Garage::displayAllModels() const {
    cout << "Liste des modèles disponibles :" << endl;
    int index = 0;
    for (list<Model>::const_iterator it = models.begin(); it != models.end(); ++it, ++index) {
        cout << "[" << index << "] " << it->toString() << endl;
    }
    cout << endl;
}

Model Garage::getModel(int index) const {
    if (index < 0 || index >= (int)models.size()) {
        // Retourner un modèle par défaut si index invalide
        return Model();
    }
    
    list<Model>::const_iterator it = models.begin();
    advance(it, index);  // Avancer de 'index' positions
    return *it;
}

//=============================================================================
// MÉTHODES POUR LES OPTIONS
//=============================================================================

void Garage::addOption(const Option& o) {
    options.push_back(o);
}

void Garage::displayAllOptions() const {
    cout << "Liste des options disponibles :" << endl;
    int index = 0;
    for (list<Option>::const_iterator it = options.begin(); it != options.end(); ++it, ++index) {
        cout << "[" << index << "] " << it->toString() << endl;
    }
    cout << endl;
}

Option Garage::getOption(int index) const {
    if (index < 0 || index >= (int)options.size()) {
        // Retourner une option par défaut si index invalide
        return Option();
    }
    
    list<Option>::const_iterator it = options.begin();
    advance(it, index);  // Avancer de 'index' positions
    return *it;
}

//=============================================================================
// MÉTHODES POUR LES CLIENTS
//=============================================================================

int Garage::addClient(string lastName, string firstName, string gsm) {
    // Incrémenter et utiliser currentNumber d'Actor pour l'ID
    Actor::currentNumber++;
    int newId = Actor::currentNumber;
    
    // Créer le nouveau client avec l'ID généré
    Client c(lastName, firstName, newId, gsm);
    
    // L'insérer dans le set (tri automatique par nom)
    clients.insert(c);
    
    return newId;
}

void Garage::displayClients() const {
    cout << "Liste des clients :" << endl;
    for (set<Client>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
        cout << it->toString() << endl;
    }
    cout << endl;
}

void Garage::deleteClientByIndex(int index) {
    if (index < 0 || index >= (int)clients.size()) {
        return;  // Index invalide
    }
    
    set<Client>::iterator it = clients.begin();
    advance(it, index);  // Avancer de 'index' positions
    clients.erase(it);   // Supprimer l'élément
}

void Garage::deleteClientById(int id) {
    // Parcourir le set pour trouver le client avec cet ID
    for (set<Client>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (it->getId() == id) {
            clients.erase(it);
            return;
        }
    }
}

Client Garage::findClientByIndex(int index) const {
    if (index < 0 || index >= (int)clients.size()) {
        return Client();  // Retourner client par défaut si index invalide
    }
    
    set<Client>::const_iterator it = clients.begin();
    advance(it, index);
    return *it;
}

Client Garage::findClientById(int id) const {
    // Parcourir le set pour trouver le client avec cet ID
    for (set<Client>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
        if (it->getId() == id) {
            return *it;
        }
    }
    return Client();  // Retourner client par défaut si non trouvé
}

//=============================================================================
// MÉTHODES POUR LES EMPLOYÉS
//=============================================================================

int Garage::addEmployee(string lastName, string firstName, string login, string role) {
    // Incrémenter et utiliser currentNumber d'Actor pour l'ID
    Actor::currentNumber++;
    int newId = Actor::currentNumber;
    
    // Créer le nouvel employé avec l'ID généré
    Employee e(lastName, firstName, newId, login, role);
    
    // L'insérer dans le set (tri automatique par nom)
    employees.insert(e);
    
    return newId;
}

void Garage::displayEmployees() const {
    cout << "Liste des employés :" << endl;
    for (set<Employee>::const_iterator it = employees.begin(); it != employees.end(); ++it) {
        cout << it->toString() << endl;
    }
    cout << endl;
}

void Garage::deleteEmployeeByIndex(int index) {
    if (index < 0 || index >= (int)employees.size()) {
        return;  // Index invalide
    }
    
    set<Employee>::iterator it = employees.begin();
    advance(it, index);  // Avancer de 'index' positions
    employees.erase(it); // Supprimer l'élément
}

void Garage::deleteEmployeeById(int id) {
    // Parcourir le set pour trouver l'employé avec cet ID
    for (set<Employee>::iterator it = employees.begin(); it != employees.end(); ++it) {
        if (it->getId() == id) {
            employees.erase(it);
            return;
        }
    }
}

Employee Garage::findEmployeeByIndex(int index) const {
    if (index < 0 || index >= (int)employees.size()) {
        return Employee();  // Retourner employé par défaut si index invalide
    }
    
    set<Employee>::const_iterator it = employees.begin();
    advance(it, index);
    return *it;
}

Employee Garage::findEmployeeById(int id) const {
    // Parcourir le set pour trouver l'employé avec cet ID
    for (set<Employee>::const_iterator it = employees.begin(); it != employees.end(); ++it) {
        if (it->getId() == id) {
            return *it;
        }
    }
    return Employee();  // Retourner employé par défaut si non trouvé
}

} // namespace carconfig
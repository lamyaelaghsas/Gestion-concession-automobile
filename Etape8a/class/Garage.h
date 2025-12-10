#ifndef GARAGE_H
#define GARAGE_H

#include <set>
#include <list>
#include <string>
#include "Employee.h"
#include "Client.h"
#include "Model.h"
#include "Option.h"

using namespace std;

namespace carconfig {

class Garage {
private:
    set<Employee> employees;    // Liste triée d'employés
    set<Client> clients;        // Liste triée de clients
    list<Model> models;         // Liste de modèles
    list<Option> options;       // Liste d'options

public:
    // Constructeur et destructeur par défaut
    Garage() = default;
    ~Garage() = default;
    
    // Méthodes pour les modèles
    void addModel(const Model& m);
    void displayAllModels() const;
    Model getModel(int index) const;
    
    // Méthodes pour les options
    void addOption(const Option& o);
    void displayAllOptions() const;
    Option getOption(int index) const;
    
    // Méthodes pour les clients
    int addClient(string lastName, string firstName, string gsm);
    void displayClients() const;
    void deleteClientByIndex(int index);
    void deleteClientById(int id);
    Client findClientByIndex(int index) const;
    Client findClientById(int id) const;
    
    // Méthodes pour les employés
    int addEmployee(string lastName, string firstName, string login, string role);
    void displayEmployees() const;
    void deleteEmployeeByIndex(int index);
    void deleteEmployeeById(int id);
    Employee findEmployeeByIndex(int index) const;
    Employee findEmployeeById(int id) const;
};

} // namespace carconfig

#endif // GARAGE_H
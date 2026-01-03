#ifndef GARAGE_H
#define GARAGE_H

#include <set>
#include <list>
#include <string>
#include "Employee.h"
#include "Client.h"
#include "Model.h"
#include "Option.h"
#include "Car.h"
#include "Credentials.h"  
#include "Contract.h" 
#include <vector> 

using namespace std;

namespace carconfig {

class Garage {
private:
    // Conteneurs
    set<Employee> employees;    // Liste triée d'employés
    set<Client> clients;        // Liste triée de clients
    list<Model> models;         // Liste de modèles
    list<Option> options;       // Liste d'options
    vector<Contract> contracts;
    
    // SINGLETON : Instance unique
    static Garage instance;
    
    // SINGLETON : Constructeur privé
    Garage();
    
    // SINGLETON : Constructeur de copie et operator= supprimés
    Garage(const Garage&) = delete;
    Garage& operator=(const Garage&) = delete;

public:
    // SINGLETON : Projet en cours (variable statique)
    static Car currentProject;

    // employé connecté
    static int idLoggedEmployee;
    
    // Destructeur
    ~Garage();
    
    // SINGLETON : Accès à l'instance unique
    static Garage& getInstance();
    
    // SINGLETON : Accès au projet en cours
    static Car& getCurrentProject();
    static void resetCurrentProject();
    
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
    set<Client> getClients() const;
    
    // Méthodes pour les employés
    int addEmployee(string lastName, string firstName, string login, string role);
    void displayEmployees() const;
    void deleteEmployeeByIndex(int index);
    void deleteEmployeeById(int id);
    Employee findEmployeeByIndex(int index) const;
    Employee findEmployeeById(int id) const;
    set<Employee> getEmployees() const;
    void updateEmployee(const Employee& emp);

    // ETAPE 13 : Méthodes pour les contrats
    int addContract(int sellerId, int clientId, const string& carProjectName);
    void deleteContractById(int id);
    void deleteContractByIndex(int index);
    Contract findContractById(int id) const;
    Contract findContractByIndex(int index) const;
    vector<Contract> getContracts() const;
    bool hasContractWithSeller(int sellerId) const;
    bool hasContractWithClient(int clientId) const;


    // IMPORT CSV
    void importModelsFromCsv(string filename);
    void importOptionsFromCsv(string filename);

    // Sérialisation
    void save();
    void load();
};

} // namespace carconfig

#endif // GARAGE_H
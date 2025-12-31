#include "../includes/Garage.h"
#include "../includes/OptionException.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream> 
#include <vector>
#include "../includes/PasswordException.h"       
#include "../includes/XmlFileSerializer.hpp"        
#include "../includes/XmlFileSerializerException.h"  
#include <cstring>
using std::vector;

using namespace std;

namespace carconfig {

// ============================================================================
// INITIALISATION DES VARIABLES STATIQUES
// ============================================================================

// Instance unique du Garage (singleton)
Garage Garage::instance;

// Projet en cours
Car Garage::currentProject;

// Employé connecté
int Garage::idLoggedEmployee = -1;

// ============================================================================
// CONSTRUCTEUR ET DESTRUCTEUR
// ============================================================================

// Constructeur privé (Singleton)
Garage::Garage() {
    Actor::currentNumber = 0;
    int id1 = addEmployee("ADMIN", "ADMIN", "admin", Employee::ADMINISTRATIVE);
}

Garage::~Garage() {
    // Destructeur par défaut
}

// ============================================================================
// MÉTHODES STATIQUES DU SINGLETON
// ============================================================================

// Retourne une référence vers l'instance unique
Garage& Garage::getInstance() {
    return instance;
}

// Retourne une référence vers le projet en cours
Car& Garage::getCurrentProject() {
    return currentProject;
}

// Réinitialise le projet en cours
void Garage::resetCurrentProject() {
    currentProject = Car();  // Crée une nouvelle Car par défaut
}

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
    for (set<Client>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (it->getId() == id) {
            clients.erase(it);
            return;  // Client trouvé et supprimé
        }
    }
    throw runtime_error("Client avec ID " + to_string(id) + " introuvable");
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

set<Client> Garage::getClients() const {
    return clients;
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
    throw runtime_error("Employe avec ID " + to_string(id) + " introuvable");
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

set<Employee> Garage::getEmployees() const {
    return employees;
}

void Garage::updateEmployee(const Employee& emp) {
    // Supprimer l'ancien employé
    deleteEmployeeById(emp.getId());
    
    // Réinsérer l'employé mis à jour
    employees.insert(emp);
}

//=============================================================================
// IMPORT CSV
//=============================================================================

void Garage::importModelsFromCsv(string filename) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "Fichier " << filename << " introuvable" << endl;
        return;
    }
    
    string line;
    
    // Lire et ignorer la première ligne (entête)
    getline(file, line);
    
    // Lire chaque ligne
    while (getline(file, line)) {
        stringstream ss(line);
        string nom, puissanceStr, moteur, image, prixStr;
        
        // Parser la ligne avec ';' comme séparateur
        getline(ss, nom, ';');
        getline(ss, puissanceStr, ';');
        getline(ss, moteur, ';');
        getline(ss, image, ';');
        getline(ss, prixStr, ';');
        
        // Convertir les strings en nombres
        int puissance = stoi(puissanceStr);
        float prix = stof(prixStr);
        
        // Déterminer le type de moteur
        Engine eng;
        if (moteur == "essence") eng = Engine::Petrol;
        else if (moteur == "diesel") eng = Engine::Diesel;
        else if (moteur == "electrique") eng = Engine::Electric;
        else if (moteur == "hybride") eng = Engine::Hybrid;
        else eng = Engine::Petrol; // par défaut
        
        // Créer et ajouter le modèle
        Model m(nom.c_str(), puissance, eng, prix);
        m.setImage(image);
        addModel(m);
    }
    
    file.close();
    cout << "Modèles importés depuis " << filename << endl;
}

void Garage::importOptionsFromCsv(string filename) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "Fichier " << filename << " introuvable" << endl;
        return;
    }
    
    string line;
    
    // Lire et ignorer la première ligne (entête)
    getline(file, line);
    
    // Lire chaque ligne
    while (getline(file, line)) {
        stringstream ss(line);
        string code, intitule, prixStr;
        
        // Parser la ligne avec ';' comme séparateur
        getline(ss, code, ';');
        getline(ss, intitule, ';');
        getline(ss, prixStr, ';');
        
        // Convertir le prix
        float prix = stof(prixStr);
        
        // Créer et ajouter l'option
        try {
            Option o(code, intitule, prix);
            addOption(o);
        } catch(OptionException& e) {
            cout << "Erreur import option: " << e.getMessage() << endl;
        }
    }
    
    file.close();
    cout << "Options importées depuis " << filename << endl;
}

// ÉTAPE 13 : GESTION DES CONTRATS
// ============================================================================

int Garage::addContract(int sellerId, int clientId, const string& carProjectName) {
    // Générer un nouvel ID pour le contrat
    static int contractIdCounter = 1;
    
    // Si on charge depuis le fichier, trouver le max ID
    if (!contracts.empty()) {
        int maxId = 0;
        for (size_t i = 0; i < contracts.size(); i++) {
            if (contracts[i].getId() > maxId) {
                maxId = contracts[i].getId();
            }
        }
        contractIdCounter = maxId + 1;
    }
    
    Contract c(contractIdCounter, sellerId, clientId, carProjectName);
    contracts.push_back(c);
    
    cout << "Contrat #" << contractIdCounter << " ajouté" << endl;
    
    return contractIdCounter++;
}

void Garage::deleteContractById(int id) {
    for (vector<Contract>::iterator it = contracts.begin(); it != contracts.end(); ++it) {
        if (it->getId() == id) {
            contracts.erase(it);
            cout << "Contrat #" << id << " supprimé" << endl;
            return;
        }
    }
    throw runtime_error("Contrat avec ID " + to_string(id) + " introuvable");
}

void Garage::deleteContractByIndex(int index) {
    if (index < 0 || index >= (int)contracts.size()) {
        throw runtime_error("Index de contrat invalide");
    }
    contracts.erase(contracts.begin() + index);
}

Contract Garage::findContractById(int id) const {
    for (size_t i = 0; i < contracts.size(); i++) {
        if (contracts[i].getId() == id) {
            return contracts[i];
        }
    }
    throw runtime_error("Contrat avec ID " + to_string(id) + " introuvable");
}

Contract Garage::findContractByIndex(int index) const {
    if (index < 0 || index >= (int)contracts.size()) {
        throw runtime_error("Index de contrat invalide");
    }
    return contracts[index];
}

vector<Contract> Garage::getContracts() const {
    return contracts;
}

bool Garage::hasContractWithSeller(int sellerId) const {
    for (size_t i = 0; i < contracts.size(); i++) {
        if (contracts[i].getSellerId() == sellerId) {
            return true;
        }
    }
    return false;
}

bool Garage::hasContractWithClient(int clientId) const {
    for (size_t i = 0; i < contracts.size(); i++) {
        if (contracts[i].getClientId() == clientId) {
            return true;
        }
    }
    return false;
}

//=============================================================================
// ÉTAPE 12 : Sauvegarde sur disque
// ============================================================================

void Garage::save() {
    cout << "=== SAUVEGARDE DU GARAGE ===" << endl;
    
    // 1. Sauvegarder les employés dans employees.xml
    try {
        XmlFileSerializer<Employee> xmlEmployees("employees.xml", XmlFileSerializer<Employee>::WRITE, "employees");
        
        for (set<Employee>::const_iterator it = employees.begin(); it != employees.end(); ++it) {
            xmlEmployees.write(*it);
        }
        
        cout << "Employés sauvegardés dans employees.xml" << endl;
    } catch(exception& e) {
        cout << "Erreur sauvegarde employés: " << e.what() << endl;
    }
    
    // 2. Sauvegarder les clients dans clients.xml
    try {
        XmlFileSerializer<Client> xmlClients("clients.xml", XmlFileSerializer<Client>::WRITE, "clients");
        
        for (set<Client>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
            xmlClients.write(*it);
        }
        
        cout << "Clients sauvegardés dans clients.xml" << endl;
    } catch(exception& e) {
        cout << "Erreur sauvegarde clients: " << e.what() << endl;
    }
    
    // 3. Sauvegarder config.dat (binaire : currentId + mots de passe cryptés)
    try {
        ofstream fichier("config.dat", ios::binary);
        
        if (!fichier) {
            cout << "Erreur ouverture config.dat" << endl;
            return;
        }
        
        // Écrire currentId
        fichier.write((char*)&Actor::currentNumber, sizeof(int));
        
        // Écrire le nombre d'employés
        int nbEmployees = employees.size();
        fichier.write((char*)&nbEmployees, sizeof(int));
        
        // Écrire les credentials (login + password cryptés)
        for (set<Employee>::const_iterator it = employees.begin(); it != employees.end(); ++it) {
            Credentials cred;
            strncpy(cred.login, it->getLogin().c_str(), 19);
            cred.login[19] = '\0';
            
            // Récupérer le mot de passe (ou vide si pas de mot de passe)
            try {
                string pwd = it->getPassword();
                strncpy(cred.password, pwd.c_str(), 19);
                cred.password[19] = '\0';
            } catch(PasswordException& e) {
                // Pas de mot de passe → chaîne vide
                cred.password[0] = '\0';
            }
            
            // Crypter
            cred.crypt();
            
            // Écrire
            fichier.write((char*)&cred, sizeof(Credentials));
        }
        
        fichier.close();
        cout << "Config sauvegardée dans config.dat" << endl;
        
    } catch(exception& e) {
        cout << "Erreur sauvegarde config: " << e.what() << endl;
    }
    try {
        XmlFileSerializer<Contract> xmlContracts("contracts.xml", XmlFileSerializer<Contract>::WRITE, "contracts");
        
        for (size_t i = 0; i < contracts.size(); i++) {
            xmlContracts.write(contracts[i]);
        }
        
        cout << "Contrats sauvegardés dans contracts.xml" << endl;
    } catch(exception& e) {
        cout << "Erreur sauvegarde contrats: " << e.what() << endl;
    }
}

void Garage::load() {
    cout << "=== CHARGEMENT DU GARAGE ===" << endl;
    
    // 1. Vérifier si config.dat existe
    ifstream testFile("config.dat", ios::binary);
    if (!testFile) {
        cout << "config.dat introuvable → premier démarrage" << endl;
        // NE PAS vider les conteneurs (ADMIN reste)
        return;
    }
    testFile.close();

    // Vider les conteneurs
    employees.clear();
    clients.clear();
    
    // 1. Charger config.dat
    try {
        ifstream fichier("config.dat", ios::binary);
        
        if (!fichier) {
            cout << "config.dat introuvable → premier démarrage" << endl;
            return;
        }
        
        // Lire currentId
        fichier.read((char*)&Actor::currentNumber, sizeof(int));
        
        // Lire le nombre d'employés
        int nbEmployees;
        fichier.read((char*)&nbEmployees, sizeof(int));
        
        // Lire les credentials
        vector<Credentials> credentialsList;
        for (int i = 0; i < nbEmployees; i++) {
            Credentials cred;
            fichier.read((char*)&cred, sizeof(Credentials));
            cred.decrypt();
            credentialsList.push_back(cred);
        }
        
        fichier.close();
        cout << "Config chargée : currentId=" << Actor::currentNumber << ", nbEmployees=" << nbEmployees << endl;
        
        // 2. Charger les employés depuis employees.xml
        try {
            XmlFileSerializer<Employee> xmlEmployees("employees.xml", XmlFileSerializer<Employee>::READ);
            
            for (int i = 0; i < nbEmployees; i++) {
                try {
                    Employee emp = xmlEmployees.read();
                    
                    // Récupérer le mot de passe correspondant
                    for (size_t j = 0; j < credentialsList.size(); j++) {
                        if (emp.getLogin() == string(credentialsList[j].login)) {
                            // Assigner le mot de passe si non vide
                            if (strlen(credentialsList[j].password) > 0) {
                                try {
                                    emp.setPassword(string(credentialsList[j].password));
                                } catch(...) {}
                            }
                            break;
                        }
                    }
                    
                    employees.insert(emp);
                    
                } catch(XmlFileSerializerException& e) {
                    if (e.getCode() == XmlFileSerializerException::END_OF_FILE) {
                        break;
                    }
                }
            }
            
            cout << "Employés chargés : " << employees.size() << endl;
            
        } catch(exception& e) {
            cout << "Erreur chargement employés: " << e.what() << endl;
        }
        
    } catch(exception& e) {
        cout << "Erreur chargement config: " << e.what() << endl;
    }
    
    // 3. Charger les clients depuis clients.xml
    try {
        XmlFileSerializer<Client> xmlClients("clients.xml", XmlFileSerializer<Client>::READ);
        
        while (true) {
            try {
                Client c = xmlClients.read();
                clients.insert(c);
            } catch(XmlFileSerializerException& e) {
                if (e.getCode() == XmlFileSerializerException::END_OF_FILE) {
                    break;
                }
            }
        }
        
        cout << "Clients chargés : " << clients.size() << endl;
        
    } catch(XmlFileSerializerException& e) {
        if (e.getCode() == XmlFileSerializerException::FILE_NOT_FOUND) {
            cout << "clients.xml introuvable → aucun client chargé" << endl;
        }
    } catch(exception& e) {
        cout << "Erreur chargement clients: " << e.what() << endl;
    }

    // ÉTAPE 13 : Charger les contrats depuis contracts.xml
    try {
        XmlFileSerializer<Contract> xmlContracts("contracts.xml", XmlFileSerializer<Contract>::READ);
        
        while (true) {
            try {
                Contract c = xmlContracts.read();
                contracts.push_back(c);
            } catch(XmlFileSerializerException& e) {
                if (e.getCode() == XmlFileSerializerException::END_OF_FILE) {
                    break;
                }
            }
        }
        
        cout << "Contrats chargés : " << contracts.size() << endl;
        
    } catch(XmlFileSerializerException& e) {
        if (e.getCode() == XmlFileSerializerException::FILE_NOT_FOUND) {
            cout << "contracts.xml introuvable → aucun contrat chargé" << endl;
        }
    } catch(exception& e) {
        cout << "Erreur chargement contrats: " << e.what() << endl;
    }
}




} // namespace carconfig
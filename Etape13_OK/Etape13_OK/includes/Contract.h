#ifndef CONTRACT_H
#define CONTRACT_H

#include <string>
#include <iostream>
using namespace std;

namespace carconfig {

class Contract {
    friend ostream& operator<<(ostream& s, const Contract& c);
    friend istream& operator>>(istream& s, Contract& c);
    
private:
    int id;              // Numéro du contrat
    int sellerId;        // ID du vendeur
    int clientId;        // ID du client
    string carProjectName;  // Nom du projet de voiture
    
public:
    // Constructeurs
    Contract();
    Contract(int id, int sellerId, int clientId, const string& carProjectName);
    Contract(const Contract& c);
    
    // Destructeur
    ~Contract();
    
    // Getters
    int getId() const;
    int getSellerId() const;
    int getClientId() const;
    string getCarProjectName() const;
    
    // Setters
    void setId(int id);
    void setSellerId(int sellerId);
    void setClientId(int clientId);
    void setCarProjectName(const string& name);
    
    // Opérateur d'affectation
    Contract& operator=(const Contract& c);
    
    // Méthode pour la table (format : id;vendeur;client;voiture)
    string tuple() const;
    
    // Affichage
    void display() const;
};

// Déclarations des opérateurs
ostream& operator<<(ostream& s, const Contract& c);
istream& operator>>(istream& s, Contract& c);

} // namespace carconfig

#endif
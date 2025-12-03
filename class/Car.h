#ifndef CAR_H
#define CAR_H

#include <string>
#include "Model.h"
#include "Option.h"

using namespace std;

namespace carconfig {

class Car
{
  friend ostream& operator<<(ostream& s, const Car& car);

private:
    string name;           // Nom du projet
    Model model;           // Modèle de base
    Option* options[5];    // Tableau de 5 pointeurs vers des options
    
    // Méthode privée pour comparer les prix
    int compP(const Car& car) const;

public:
    // Constructeurs
    Car();
    Car(const string& n, const Model& m);
    Car(const Car& car);
    
    // Destructeur
    ~Car();
    
    // Getters
    string getName() const;
    const Model& getModel() const;
    float getPrice() const;  // Prix total (modèle + options)
    
    // Setters
    void setName(const string& n);
    void setModel(const Model& m);
    
    // Gestion des options
    void addOption(const Option& option);
    void removeOption(string code);
    
    // Affichage
    void display() const;
    
    // OPÉRATEURS
    // Opérateur d'affectation
    Car& operator=(const Car& car);
    
    // Opérateurs d'addition (ajouter une option)
    Car operator+(const Option& option) const;
    friend Car operator+(const Option& option, const Car& car);
    
    // Opérateurs de soustraction (retirer une option)
    Car operator-(const Option& option) const;
    Car operator-(const string& code) const;
    
    // Opérateurs de comparaison (sur le prix)
    int operator<(const Car& car) const;
    int operator>(const Car& car) const;
    int operator==(const Car& car) const;
    Option* operator[](int i) const;

};

} // namespace carconfig

#endif
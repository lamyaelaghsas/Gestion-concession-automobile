#ifndef CAR_H
#define CAR_H

#include <string>
#include "Model.h"
#include "Option.h"

using namespace std;

namespace carconfig {

class Car
{
private:
    string name;           // Nom du projet
    Model model;           // Modèle de base
    Option* options[5];    // Tableau de 5 pointeurs vers des options

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
};

} // namespace carconfig

#endif
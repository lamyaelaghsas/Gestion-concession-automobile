#include "Car.h"
#include <iostream>
#include <iomanip>

using namespace std;

namespace carconfig {

// Constructeur par défaut
Car::Car()
{
    name = "";
    // Initialiser tous les pointeurs à nullptr
    for (int i = 0; i < 5; i++)
    {
        options[i] = nullptr;
    }
}

// Constructeur d'initialisation
Car::Car(const string& n, const Model& m)
{
    name = n;
    setModel(m);  // Utilise setModel pour la copie profonde
    
    // Initialiser tous les pointeurs à nullptr
    for (int i = 0; i < 5; i++)
    {
        options[i] = nullptr;
    }
}

// Constructeur de copie
Car::Car(const Car& car)
{
    name = car.name;
    setModel(car.model);  // Utilise setModel pour la copie profonde
    
    // Copie profonde des options
    for (int i = 0; i < 5; i++)
    {
        if (car.options[i] != nullptr)
        {
            // Allouer une nouvelle option et copier le contenu
            options[i] = new Option(*(car.options[i]));
        }
        else
        {
            options[i] = nullptr;
        }
    }
}

// Destructeur
Car::~Car()
{
    // Libérer toutes les options allouées dynamiquement
    for (int i = 0; i < 5; i++)
    {
        if (options[i] != nullptr)
        {
            delete options[i];
            options[i] = nullptr;
        }
    }
}

// Getters
string Car::getName() const
{
    return name;
}

const Model& Car::getModel() const
{
    return model;
}

// Calcul du prix total
float Car::getPrice() const
{
    float totalPrice = model.getBasePrice();
    
    // Ajouter le prix de chaque option
    for (int i = 0; i < 5; i++)
    {
        if (options[i] != nullptr)
        {
            totalPrice += options[i]->getPrice();
        }
    }
    
    return totalPrice;
}

// Setters
void Car::setName(const string& n)
{
    name = n;
}

void Car::setModel(const Model& m)
{
    model.setName(m.getName());
    model.setPower(m.getPower());
    model.setEngine(m.getEngine());
    model.setBasePrice(m.getBasePrice());
}

// Ajouter une option
void Car::addOption(const Option& option)
{
    // Chercher une place libre
    for (int i = 0; i < 5; i++)
    {
        if (options[i] == nullptr)
        {
            // Allouer dynamiquement une nouvelle option
            options[i] = new Option(option);
            cout << "Option ajoutee a l'indice " << i << endl;
            return;
        }
    }
    
    cout << "Erreur: Impossible d'ajouter l'option (tableau plein)" << endl;
}

// Retirer une option par code
void Car::removeOption(string code)
{
    for (int i = 0; i < 5; i++)
    {
        if (options[i] != nullptr && options[i]->getCode() == code)
        {
            delete options[i];
            options[i] = nullptr;
            cout << "Option " << code << " supprimee" << endl;
            return;
        }
    }
    
    cout << "Erreur: Option " << code << " non trouvee" << endl;
}

// Affichage
void Car::display() const
{
    cout << "=== Projet de voiture ===" << endl;
    cout << "Nom du projet : " << name << endl;
    cout << "--- Modele ---" << endl;
    model.display();
    
    cout << "--- Options ---" << endl;
    bool hasOptions = false;
    for (int i = 0; i < 5; i++)
    {
        if (options[i] != nullptr)
        {
            cout << "Option " << (i+1) << " :" << endl;
            options[i]->display();
            hasOptions = true;
        }
    }
    
    if (!hasOptions)
    {
        cout << "Aucune option" << endl;
    }
    
    cout << fixed << setprecision(2);
    cout << "Prix total : " << getPrice() << " euros" << endl;
}

} // namespace carconfig
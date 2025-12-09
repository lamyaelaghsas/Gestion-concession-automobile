#include "Car.h"
#include "OptionException.h"
#include <iostream>
#include <iomanip>

using namespace std;

namespace carconfig {

//=============================================================================
// CONSTRUCTEURS
//=============================================================================

Car::Car()
{
    name = "";
    
    // Initialiser toutes les options à nullptr
    for (int i = 0; i < 5; i++)
    {
        options[i] = nullptr;
    }
}

Car::Car(const string& n, const Model& m)
{
    name = n;
    setModel(m);
    
    // Initialiser toutes les options à nullptr
    for (int i = 0; i < 5; i++)
    {
        options[i] = nullptr;
    }
}

Car::Car(const Car& car)
{
    name = car.name;
    setModel(car.model);
    
    // Initialiser à nullptr
    for (int i = 0; i < 5; i++)
    {
        options[i] = nullptr;
    }
    
    // Copier les options
    int i = 0;
    while (i < 5)
    {
        if (car.options[i] != nullptr)
        {
            options[i] = new Option();
            options[i]->setCode(car.options[i]->getCode());
            options[i]->setLabel(car.options[i]->getLabel());
            options[i]->setPrice(car.options[i]->getPrice());
        }
        i++;
    }
}

//=============================================================================
// DESTRUCTEUR
//=============================================================================

Car::~Car()
{
    for (int i = 0; i < 5; i++)
    {
        if (options[i] != nullptr)
            delete options[i];
    }
}

//=============================================================================
// SETTERS
//=============================================================================

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

//=============================================================================
// GETTERS
//=============================================================================

string Car::getName() const
{
    return name;
}

const Model& Car::getModel() const
{
    return model;
}

float Car::getPrice() const
{
    float total = model.getBasePrice();
    
    for (int i = 0; i < 5; i++)
    {
        if (options[i] != nullptr)
        {
            total += options[i]->getPrice();
        }
    }
    
    return total;
}

//=============================================================================
// GESTION DES OPTIONS
//=============================================================================

void Car::addOption(const Option& option)
{
    // Vérifier si l'option existe déjà
    int i = 0;
    while (i < 5)
    {
        if (options[i] != nullptr)
        {
            if (options[i]->getCode() == option.getCode())
            {
                throw OptionException("Cette option a deja ete ajoutee");
            }
        }
        i++;
    }
    
    // Trouver la première place libre
    i = 0;
    while (i < 5 && options[i] != nullptr)
    {
        i++;
    }
    
    // Vérifier s'il reste de la place
    if (i == 5)
    {
        throw OptionException("La limite d'options a ete atteinte");
    }
    
    // Ajouter l'option
    options[i] = new Option();
    options[i]->setCode(option.getCode());
    options[i]->setLabel(option.getLabel());
    options[i]->setPrice(option.getPrice());
}

void Car::removeOption(string code)
{
    int i = 0;
    int found = 0;
    
    while (i < 5)
    {
        if (options[i] != nullptr)
        {
            if (options[i]->getCode() == code)
            {
                delete options[i];
                options[i] = nullptr;
                found = 1;
                i = 5; // Sortir de la boucle
            }
        }
        i++;
    }
    
    if (found == 0)
    {
        throw OptionException("Cette option n'existe pas");
    }
}

//=============================================================================
// AFFICHAGE
//=============================================================================

void Car::display() const
{
    cout << "Nom: " << name << endl;
    
    // Afficher le modèle
    model.display();
    
    // Afficher les options
    for (int i = 0; i < 5; i++)
    {
        if (options[i] != nullptr)
        {
            options[i]->display();
            cout << endl;
        }
    }
    
    // Afficher le prix total
    cout << "Prix total: " << fixed << setprecision(2) << getPrice() << " euros" << endl;
}

//=============================================================================
// OPÉRATEURS
//=============================================================================

// Opérateur d'affectation =
Car& Car::operator=(const Car& car)
{
    // Copier le nom et le modèle
    name = car.name;
    setModel(car.model);
    
    // Libérer la mémoire existante des options
    for (int i = 0; i < 5; i++)
    {
        if (options[i] != nullptr)
        {
            delete options[i];
        }
    }
    
    // Réinitialiser à nullptr
    for (int i = 0; i < 5; i++)
    {
        options[i] = nullptr;
    }
    
    // Copier les options
    int i = 0;
    while (i < 5)
    {
        if (car.options[i] != nullptr)
        {
            options[i] = new Option();
            options[i]->setCode(car.options[i]->getCode());
            options[i]->setLabel(car.options[i]->getLabel());
            options[i]->setPrice(car.options[i]->getPrice());
        }
        i++;
    }
    
    return (*this);
}

// Opérateur de comparaison <
int Car::operator<(const Car& car) const
{
    return comparePrice(car) == -1;
}

// Opérateur de comparaison >
int Car::operator>(const Car& car) const
{
    return comparePrice(car) == 1;
}

// Opérateur de comparaison ==
int Car::operator==(const Car& car) const
{
    return comparePrice(car) == 0;
}

// Opérateur d'addition + (Car + Option)
Car Car::operator+(const Option& option) const
{
    Car c2(*this);
    c2.addOption(option);
    return c2;
}

// Opérateur de soustraction - (Car - Option)
Car Car::operator-(const Option& option) const
{
    return (*this) - option.getCode();
}

// Opérateur de soustraction - (Car - string)
Car Car::operator-(const string& code) const
{
    Car c2(*this);
    c2.removeOption(code);
    return c2;
}

// Opérateur [] - Accès aux options par indice
Option* Car::operator[](int i) const
{
    if (i < 0 || i >= 5)
    {
        return nullptr;
    }
    return options[i];
}

//=============================================================================
// MÉTHODE AUXILIAIRE PRIVÉE
//=============================================================================

int Car::comparePrice(const Car& car) const
{
    if (getPrice() < car.getPrice()) return -1;
    if (getPrice() > car.getPrice()) return 1;
    return 0;
}

//=============================================================================
// OPÉRATEUR D'INSERTION <<
//=============================================================================

ostream& operator<<(ostream& s, const Car& car)
{
    s << "Nom : " << car.name << endl;
    s << car.model;
    
    for (int i = 0; i < 5; i++)
    {
        if (car.options[i] != nullptr)
        {
            s << *(car.options[i]);
        }
    }
    
    return s;
}

// Opérateur ami : Option + Car
Car operator+(const Option& option, const Car& car)
{
    return car + option;
}

} // namespace carconfig
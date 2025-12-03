#include "Car.h"
#include <iostream>
#include <iomanip>

using namespace std;

namespace carconfig {

//=============================================================================
// CONSTRUCTEURS
//=============================================================================

Car::Car()
{
    cout << "Car: Constructeur par defaut" << endl;
    name = "";
    
    // Initialiser toutes les options à nullptr
    for (int i = 0; i < 5; i++)
    {
        options[i] = nullptr;
    }
}

Car::Car(const string& n, const Model& m)
{
    cout << "Car: Constructeur d'initialisation" << endl;
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
    cout << "Car: Constructeur de copie" << endl;
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
    cout << "Car: Destructeur" << endl;
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
                cout << "Erreur: Cette option a deja ete ajoutee" << endl;
                return;
            }
        }
        i++;
    }
    
    // Trouver une place libre
    i = 0;
    while (i < 5 && options[i] != nullptr)
    {
        i++;
    }
    
    if (i == 5)
    {
        cout << "Erreur: La limite d'options a ete atteinte" << endl;
        return;
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
    int trouve = 0;
    
    while (i < 5)
    {
        if (options[i] != nullptr)
        {
            if (options[i]->getCode() == code)
            {
                delete options[i];
                options[i] = nullptr;
                i = 5;  // Sortir de la boucle
                trouve = 1;
            }
        }
        i++;
    }
    
    if (trouve == 0)
    {
        cout << "Erreur: Cette option n'existe pas" << endl;
    }
}

//=============================================================================
// AFFICHAGE
//=============================================================================

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

//=============================================================================
// OPÉRATEURS
//=============================================================================

// Opérateur d'affectation =
Car& Car::operator=(const Car& car)
{
    name = car.name;
    setModel(car.model);
    
    // Libérer les anciennes options
    for (int i = 0; i < 5; i++)
    {
        if (options[i] != nullptr)
            delete options[i];
    }
    
    // Réinitialiser
    for (int i = 0; i < 5; i++)
    {
        options[i] = nullptr;
    }
    
    // Copier les nouvelles options
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

// Opérateur + (Car + Option)
Car Car::operator+(const Option& o) const
{
    Car c2(*this);
    c2.addOption(o);
    return c2;
}

// Opérateur + (Option + Car) - FONCTION AMIE
Car operator+(const Option& o, const Car& c)
{
    return c + o;
}

// Opérateur - (Car - Option)
Car Car::operator-(const Option& o) const
{
    return (*this) - o.getCode();
}

// Opérateur - (Car - string)
Car Car::operator-(const string& code) const
{
    Car c2(*this);
    c2.removeOption(code);
    return c2;
}

// Méthode privée de comparaison
int Car::compP(const Car& car) const
{
    if (getPrice() < car.getPrice()) return -1;
    if (getPrice() > car.getPrice()) return 1;
    return 0;
}

// Opérateur 
int Car::operator<(const Car& car) const
{
    return compP(car) == -1;
}

// Opérateur >
int Car::operator>(const Car& car) const
{
    return compP(car) == 1;
}

// Opérateur ==
int Car::operator==(const Car& car) const
{
    return compP(car) == 0;
}

// Opérateur << (FONCTION AMIE)
ostream& operator<<(ostream& s, const Car& car)
{
    s << "Nom: " << car.name << endl;
    s << car.model;
    
    for (int i = 0; i < 5; i++)
    {
        if (car.options[i] != nullptr)
        {
            s << *(car.options[i]);
            s << endl;
        }
    }
    
    return s;
}

// Opérateur []
Option* Car::operator[](const int i) const
{
    return options[i];
}

} // namespace carconfig
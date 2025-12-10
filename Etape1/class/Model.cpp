#include "Model.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

namespace carconfig { 

//=============================================================================
// CONSTRUCTEURS
//=============================================================================

Model::Model() // constructeur par défaut
{
    name = nullptr;
    setName("default"); //on donne un nom par defaut 
    setPower(80); //puissance du moteur
    setEngine(Engine::Petrol); //type du moteur 
    setBasePrice(15000);
}

Model::Model(const char* n, int p, Engine e, float bp) // constructeur d'initialisation
{
    name = nullptr;
    setName(n);
    setPower(p);
    setEngine(e);
    setBasePrice(bp);
}

Model::Model(const Model& mod) // constructeur de copie
{
    name = nullptr;
    setName(mod.getName());
    setPower(mod.getPower());
    setEngine(mod.getEngine());
    setBasePrice(mod.getBasePrice());
}

//=============================================================================
// DESTRUCTEUR
//=============================================================================

Model::~Model()
{
    if (name != nullptr) delete[] name;
}

//=============================================================================
// SETTERS
//=============================================================================

void Model::setPower(int p)
{
    if(p >= 0) power = p;
}

void Model::setName(const char* n)
{
    if (name != nullptr) delete[] name; // libérer l’ancienne mémoire si elle existait
    name = new char[strlen(n)+1];
    strcpy(name, n);
}

void Model::setEngine(Engine e)
{
    engine = e;
}

void Model::setBasePrice(float bp)
{
    basePrice = bp;
}

//=============================================================================
// GETTERS
//=============================================================================

int Model::getPower() const
{
    return power;
}

const char* Model::getName() const
{
    return name;
}

Engine Model::getEngine() const
{
    return engine;
}

float Model::getBasePrice() const
{
    return basePrice;
}

//=============================================================================
// AFFICHAGE
//=============================================================================

void Model::display() const
{
    cout << "Nom : " << name << endl;
    cout << "Puissance : " << power << " ch" << endl;
    cout << "Moteur : ";
    switch(engine) {
        case Engine::Petrol: cout << "Essence"; break;
        case Engine::Diesel: cout << "Diesel"; break;
        case Engine::Electric: cout << "Electrique"; break;
        case Engine::Hybrid: cout << "Hybride"; break;
    }
    cout << endl;
    cout << fixed << setprecision(2);
    cout << "Prix de base : " << basePrice << " euros" << endl;
}


} // namespace carconfig
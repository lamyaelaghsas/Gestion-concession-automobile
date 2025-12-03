#include "Model.h"
#include <iostream>
#include <cstring>

using namespace std;

namespace carconfig { 

Model::Model() // constructeur par défaut
{
    cout << "Constructeur par defaut" << endl;
    name = nullptr;
    setName("default");  
    setPower(80);
    setEngine(Engine::Petrol);
    setBasePrice(15000);
}

Model::Model(const char* n, int p, Engine e, float bp) // constructeur d'initialisation
{
    cout << "Constructeur d'initialisation" << endl;
    name = nullptr;
    setName(n);
    setPower(p);
    setEngine(e);
    setBasePrice(bp);
}

Model::Model(const Model& mod) // constructeur de copie
{
    cout << "Constructeur de copie" << endl;
    name = nullptr;
    setName(mod.getName());
    setPower(mod.getPower());
    setEngine(mod.getEngine());
    setBasePrice(mod.getBasePrice());
}

Model::~Model()
{
    cout << "Destructeur" << endl;
    if (name != nullptr) delete[] name;  // delete[] pour un tableau
}

void Model::setPower(int p)
{
    if(p >= 0) power = p;
}

int Model::getPower() const
{
    return power;
}

void Model::setName(const char* n)
{
    if (name != nullptr) delete[] name; // ← Libère "default" de la mémoire
    name = new char[strlen(n)+1];
    strcpy(name,n);
}

const char* Model::getName() const
{
    return name;
}

void Model::setEngine(Engine e)
{
    engine = e;
}

Engine Model::getEngine() const
{
    return engine;
}

void Model::setBasePrice(float bp)
{
    basePrice = bp;
}

float Model::getBasePrice() const
{
    return basePrice;
}

void Model::display() const
{
    cout << "Nom : " << name << endl;
    cout << "Puissance : " << power << endl;
    cout << "Moteur : ";
    switch(engine) {
        case Engine::Petrol: cout << "Essence"; break;
        case Engine::Diesel: cout << "Diesel"; break;
        case Engine::Electric: cout << "Electrique"; break;
        case Engine::Hybrid: cout << "Hybride"; break;
    }
    cout << endl;
    cout << "Prix de base : " << basePrice << endl;
}

ostream& operator<<(ostream& s, const Model& m)
{
    s << "Nom : " << m.name << endl;
    s << "Puissance : " << m.power << endl;
    s << "Moteur : ";
    switch(m.engine) {
        case Engine::Petrol: s << "Essence"; break;
        case Engine::Diesel: s << "Diesel"; break;
        case Engine::Electric: s << "Electrique"; break;
        case Engine::Hybrid: s << "Hybride"; break;
    }
    s << endl;
    s << fixed << setprecision(2);
    s << "Prix de base : " << m.basePrice << endl;
    return s;
}

} 
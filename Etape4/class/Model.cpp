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
    setName("default");  
    setPower(80);
    setEngine(Engine::Petrol);
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
    if (name != nullptr) delete[] name;
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

//=============================================================================
// OPÉRATEURS D'INSERTION/EXTRACTION
//=============================================================================

ostream& operator<<(ostream& s, const Model& m)
{
    s << "Nom : " << m.name << endl;
    s << "Puissance : " << m.power << " ch" << endl;
    s << "Moteur : ";
    switch(m.engine) {
        case Engine::Petrol: s << "Essence"; break;
        case Engine::Diesel: s << "Diesel"; break;
        case Engine::Electric: s << "Electrique"; break;
        case Engine::Hybrid: s << "Hybride"; break;
    }
    s << endl;
    s << fixed << setprecision(2);
    s << "Prix de base : " << m.basePrice << " euros" << endl;
    return s;
}

istream& operator>>(istream& s, Model& m)
{
    string n;
    int p, choix;
    Engine eng;
    float bp;
    
    cout << "Encoder le nom : ";
    getline(s, n);
    
    cout << "Encoder la puissance : ";
    s >> p;
    
    do
    {
        cout << "Quel type de moteur ?" << endl;
        cout << "1 - Essence" << endl;
        cout << "2 - Diesel" << endl;
        cout << "3 - Electrique" << endl;
        cout << "4 - Hybride" << endl;
        cout << "Choix : ";
        s >> choix;
        
        if (choix <= 0 || choix > 4)
            cout << "CHOIX INVALIDE : ENCODER ENCORE\n\n";
    }
    while (choix <= 0 || choix > 4);
    
    switch(choix)
    {
        case 1: eng = Engine::Petrol; break;
        case 2: eng = Engine::Diesel; break;
        case 3: eng = Engine::Electric; break;
        case 4: eng = Engine::Hybrid; break;
    }
    
    cout << "Encoder le prix de base : ";
    s >> bp;
    
    m.setName(n.c_str());
    m.setPower(p);
    m.setEngine(eng);
    m.setBasePrice(bp);
    
    return s;
}

} // namespace carconfig
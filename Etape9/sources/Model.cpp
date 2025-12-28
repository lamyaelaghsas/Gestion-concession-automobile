#include "Model.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <fstream>

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
// OPÉRATEURS D'INSERTION/EXTRACTION (FORMAT XML pour sérialisation)
//=============================================================================

ostream& operator<<(ostream& s, const Model& m)
{
    s << "<Model>" << endl;
    s << "<name>" << endl;
    s << m.name << endl;
    s << "</name>" << endl;
    s << "<power>" << endl;
    s << m.power << endl;
    s << "</power>" << endl;
    s << "<engine>" << endl;
    
    // Écriture du type de moteur en texte
    switch(m.engine) {
        case Engine::Petrol: s << "essence"; break;
        case Engine::Diesel: s << "diesel"; break;
        case Engine::Electric: s << "electrique"; break;
        case Engine::Hybrid: s << "hybride"; break;
    }
    s << endl;
    
    s << "</engine>" << endl;
    s << "<basePrice>" << endl;
    s << m.basePrice << endl;
    s << "</basePrice>" << endl;
    s << "</Model>" << endl;
    
    return s;
}

istream& operator>>(istream& s, Model& m)
{
    string line;
    
    // Lire <Model>
    getline(s, line);
    
    // Lire <name>
    getline(s, line);
    
    // Lire la valeur du name
    getline(s, line);
    m.setName(line.c_str());
    
    // Lire </name>
    getline(s, line);
    
    // Lire <power>
    getline(s, line);
    
    // Lire la valeur du power
    getline(s, line);
    m.setPower(stoi(line));
    
    // Lire </power>
    getline(s, line);
    
    // Lire <engine>
    getline(s, line);
    
    // Lire la valeur du moteur
    getline(s, line);
    if (line == "essence") m.setEngine(Engine::Petrol);
    else if (line == "diesel") m.setEngine(Engine::Diesel);
    else if (line == "electrique") m.setEngine(Engine::Electric);
    else if (line == "hybride") m.setEngine(Engine::Hybrid);
    
    // Lire </engine>
    getline(s, line);
    
    // Lire <basePrice>
    getline(s, line);
    
    // Lire la valeur du basePrice
    getline(s, line);
    m.setBasePrice(stof(line));
    
    // Lire </basePrice>
    getline(s, line);
    
    // Lire </Model>
    getline(s, line);
    
    return s;
}

//=============================================================================
// MÉTHODE toString() POUR AFFICHAGE CONSOLE
//=============================================================================

string Model::toString() const
{
    stringstream ss;
    ss << "Nom : " << name << endl;
    ss << "Puissance : " << power << " ch" << endl;
    ss << "Moteur : ";
    switch(engine) {
        case Engine::Petrol: ss << "Essence"; break;
        case Engine::Diesel: ss << "Diesel"; break;
        case Engine::Electric: ss << "Electrique"; break;
        case Engine::Hybrid: ss << "Hybride"; break;
    }
    ss << endl;
    ss << fixed << setprecision(2);
    ss << "Prix de base : " << basePrice << " euros";
    return ss.str();
}

//=============================================================================
// OPÉRATEUR D'AFFECTATION
//=============================================================================

Model& Model::operator=(const Model& m)
{
    if (this != &m)
    {
        setName(m.getName());
        setPower(m.getPower());
        setEngine(m.getEngine());
        setBasePrice(m.getBasePrice());
    }
    return *this;
}

} // namespace carconfig
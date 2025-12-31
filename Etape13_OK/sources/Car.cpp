#include "../includes/Car.h"
#include "../includes/OptionException.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

namespace carconfig {

//=============================================================================
// CONSTRUCTEURS
//=============================================================================

Car::Car()
{
    name = "";
    
    for (int i = 0; i < 5; i++)
    {
        options[i] = nullptr;
    }
}

Car::Car(const string& n, const Model& m)
{
    name = n;
    setModel(m);
    
    for (int i = 0; i < 5; i++)
    {
        options[i] = nullptr;
    }
}

Car::Car(const Car& car)
{
    name = car.name;
    setModel(car.model);
    
    for (int i = 0; i < 5; i++)
    {
        options[i] = nullptr;
    }
    
    // Copie profonde des options
    for (int i = 0; i < 5; i++)
    {
        if (car.options[i] != nullptr)
        {
            options[i] = new Option(*car.options[i]);
        }
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
        {
            delete options[i];
            options[i] = nullptr;
        }
    }
}

//=============================================================================
// GETTERS
//=============================================================================

string Car::getName() const
{
    return name;
}

Model Car::getModel() const
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
// SETTERS
//=============================================================================

void Car::setName(const string& n)
{
    name = n;
}

void Car::setModel(const Model& m)
{
    model = m;
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
                i = 5;
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
    cout << "Nom du projet : " << name << endl;
    cout << "Modele : " << endl;
    model.display();
    
    cout << "Options :" << endl;
    int count = 0;
    for (int i = 0; i < 5; i++)
    {
        if (options[i] != nullptr)
        {
            cout << "  Option " << (i+1) << " : " << endl;
            options[i]->display();
            count++;
        }
    }
    
    if (count == 0)
    {
        cout << "  Aucune option" << endl;
    }
    
    cout << fixed << setprecision(2);
    cout << "Prix total : " << getPrice() << " euros" << endl;
}

string Car::toString() const
{
    stringstream ss;
    ss << "Nom du projet : " << name << endl;
    ss << "Modele : " << endl;
    ss << model.toString() << endl;
    
    ss << "Options :" << endl;
    int count = 0;
    for (int i = 0; i < 5; i++)
    {
        if (options[i] != nullptr)
        {
            ss << "  Option " << (i+1) << " : " << endl;
            ss << options[i]->toString() << endl;
            count++;
        }
    }
    
    if (count == 0)
    {
        ss << "  Aucune option" << endl;
    }
    
    ss << fixed << setprecision(2);
    ss << "Prix total : " << getPrice() << " euros";
    
    return ss.str();
}

//=============================================================================
// OPÉRATEURS D'AFFECTATION
//=============================================================================

Car& Car::operator=(const Car& car)
{
    if (this != &car)
    {
        name = car.name;
        setModel(car.model);
        
        // Libérer les anciennes options
        for (int i = 0; i < 5; i++)
        {
            if (options[i] != nullptr)
            {
                delete options[i];
                options[i] = nullptr;
            }
        }
        
        // Copie profonde des nouvelles options
        for (int i = 0; i < 5; i++)
        {
            if (car.options[i] != nullptr)
            {
                options[i] = new Option(*car.options[i]);
            }
        }
    }
    
    return *this;
}

//=============================================================================
// OPÉRATEURS ARITHMÉTIQUES
//=============================================================================

Car Car::operator+(const Option& opt) const
{
    Car temp(*this);
    temp.addOption(opt);
    return temp;
}

Car operator+(const Option& opt, const Car& car)
{
    return car + opt;
}

Car Car::operator-(const Option& opt) const
{
    Car temp(*this);
    temp.removeOption(opt.getCode());
    return temp;
}

Car Car::operator-(const string& code) const
{
    Car temp(*this);
    temp.removeOption(code);
    return temp;
}

//=============================================================================
// OPÉRATEURS DE COMPARAISON
//=============================================================================

int Car::comparePrice(const Car& car) const
{
    float p1 = getPrice();
    float p2 = car.getPrice();
    
    if (p1 < p2) return -1;
    if (p1 > p2) return 1;
    return 0;
}

int Car::operator<(const Car& car) const
{
    return comparePrice(car) == -1;
}

int Car::operator>(const Car& car) const
{
    return comparePrice(car) == 1;
}

int Car::operator==(const Car& car) const
{
    return comparePrice(car) == 0;
}

//=============================================================================
// OPÉRATEUR D'INDEXATION
//=============================================================================

Option* Car::operator[](int index) const
{
    if (index < 0 || index >= 5)
    {
        return nullptr;
    }
    return options[index];
}

//=============================================================================
// OPÉRATEURS D'INSERTION/EXTRACTION (FORMAT XML pour sérialisation)
//=============================================================================

ostream& operator<<(ostream& s, const Car& car)
{
    s << "<Car>" << endl;
    s << "<n>" << endl;
    s << car.name << endl;
    s << "</n>" << endl;
    s << "<model>" << endl;
    s << car.model;  // Appelle operator<< de Model
    s << "</model>" << endl;
    s << "<options>" << endl;
    
    // Écrire toutes les options présentes
    for (int i = 0; i < 5; i++)
    {
        if (car.options[i] != nullptr)
        {
            s << *car.options[i];  // Appelle operator<< de Option
        }
    }
    
    s << "</options>" << endl;
    s << "</Car>" << endl;
    
    return s;
}

istream& operator>>(istream& s, Car& car)
{
    string line;
    
    // Lire <Car>
    getline(s, line);
    
    // Lire <n>
    getline(s, line);
    
    // Lire la valeur du name
    getline(s, line);
    car.setName(line);
    
    // Lire </n>
    getline(s, line);
    
    // Lire <model>
    getline(s, line);
    
    // Lire le Model (appelle operator>> de Model)
    Model m;
    s >> m;
    car.setModel(m);
    
    // Lire </model>
    getline(s, line);
    
    // Lire <options>
    getline(s, line);
    
    // Libérer les anciennes options
    for (int i = 0; i < 5; i++)
    {
        if (car.options[i] != nullptr)
        {
            delete car.options[i];
            car.options[i] = nullptr;
        }
    }
    
    // Lire les options jusqu'à </options>
    int optionIndex = 0;
    while (true)
    {
        // Sauvegarder la position actuelle
        streampos pos = s.tellg();
        
        // Lire une ligne
        getline(s, line);
        
        // Si c'est </options>, on arrête
        if (line == "</options>")
        {
            break;
        }
        
        // Sinon, revenir en arrière et lire une option
        s.seekg(pos);
        
        if (optionIndex < 5)
        {
            car.options[optionIndex] = new Option();
            s >> *car.options[optionIndex];  // Appelle operator>> de Option
            optionIndex++;
        }
    }
    
    // Lire </Car>
    getline(s, line);
    
    return s;
}


//=============================================================================
// METHODES SAVE ET LOAD
//=============================================================================

void Car::save()
{
    // 1. Créer le nom du fichier
    string filename = name + ".xml";
    
    // 2. Ouvrir le fichier en écriture
    ofstream file(filename);
    
    if (!file.is_open())
    {
        throw runtime_error("Impossible de créer le fichier");
    }
    
    // 3. Écrire l'entête XML
    file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
    
    // 4. Utiliser l'opérateur << pour sérialiser
    file << *this;
    
    // 5. Fermer le fichier
    file.close();
}

void Car::load(string projectName)
{
    // 1. Créer le nom du fichier
    string filename = projectName + ".xml";
    
    // 2. Ouvrir le fichier en lecture
    ifstream file(filename);
    
    if (!file.is_open())
    {
        throw runtime_error("Fichier introuvable");
    }
    
    // 3. Lire l'entête XML (on ne l'utilise pas)
    string line;
    getline(file, line);
    
    // 4. Utiliser l'opérateur >> pour désérialiser
    file >> *this;
    
    // 5. Fermer le fichier
    file.close();
}

} // namespace carconfig
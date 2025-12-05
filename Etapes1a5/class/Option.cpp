#include "Option.h"
#include "OptionException.h"
#include <iostream>
#include <iomanip>

using namespace std;

namespace carconfig {

//=============================================================================
// CONSTRUCTEURS
//=============================================================================

Option::Option()
{
    cout << "Option: Constructeur par defaut" << endl;
    code = "";
    label = "";
    price = 0.0f;
}

Option::Option(const string& c, const string& l, float p)
{
    cout << "Option: Constructeur d'initialisation" << endl;
    setCode(c);
    setLabel(l);
    setPrice(p);
}

Option::Option(const Option& opt)
{
    cout << "Option: Constructeur de copie" << endl;
    code = opt.code;
    label = opt.label;
    price = opt.price;
}

//=============================================================================
// DESTRUCTEUR
//=============================================================================

Option::~Option()
{
    cout << "Option: Destructeur" << endl;
}

//=============================================================================
// GETTERS
//=============================================================================

string Option::getCode() const
{
    return code;
}

string Option::getLabel() const
{
    return label;
}

float Option::getPrice() const
{
    return price;
}

//=============================================================================
// SETTERS
//=============================================================================

void Option::setCode(const string& c)
{
    if (c.length() != 4)
    {
        throw OptionException("Longueur invalide pour le code (Min/Max = 4)");
    }
    code = c;
}

void Option::setLabel(const string& l)
{
    if (l.length() == 0)
    {
        throw OptionException("Longueur invalide pour l'intitule");
    }
    label = l;
}

void Option::setPrice(float p)
{
    if (p < 0.0)
    {
        throw OptionException("Le prix ne peut pas etre negatif");
    }
    price = p;
}

//=============================================================================
// AFFICHAGE
//=============================================================================

void Option::display() const
{
    cout << "Code : " << code << endl;
    cout << "Intitule : " << label << endl;
    cout << fixed << setprecision(2);
    cout << "Prix : " << price << " euros" << endl;
}

//=============================================================================
// OPÉRATEURS D'INSERTION/EXTRACTION
//=============================================================================

ostream& operator<<(ostream& s, const Option& opt)
{
    s << "Code : " << opt.code << endl;
    s << "Intitule : " << opt.label << endl;
    s << fixed << setprecision(2);
    s << "Prix : " << opt.price << " euros" << endl;
    return s;
}

istream& operator>>(istream& s, Option& opt)
{
    string c, l;
    float p;
    
    cout << "Encoder le code : ";
    s >> c;
    opt.setCode(c);
    
    s.ignore(); // Vider le buffer
    
    cout << "Encoder l'intitule : ";
    getline(s, l);
    opt.setLabel(l);
    
    cout << "Encoder le prix : ";
    s >> p;
    opt.setPrice(p);
    
    s.ignore(); // Vider le buffer
    
    return s;
}

//=============================================================================
// OPÉRATEURS DE DÉCRÉMENTATION
//=============================================================================

// Pré-décrémentation : --option
Option& Option::operator--()
{
    float p = getPrice();
    
    if ((p - 50.0) < 0.0)
    {
        throw OptionException("Le prix ne peut pas etre negatif");
    }
    
    setPrice(p - 50.0);
    return (*this);
}

// Post-décrémentation : option--
Option Option::operator--(int)
{
    Option temp(*this);
    
    float p = getPrice();
    
    if ((p - 50.0) < 0.0)
    {
        throw OptionException("Le prix ne peut pas etre negatif");
    }
    
    setPrice(p - 50.0);
    return temp;
}

} // namespace carconfig
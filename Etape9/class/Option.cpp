#include "Option.h"
#include "OptionException.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

namespace carconfig {

//=============================================================================
// CONSTRUCTEURS
//=============================================================================

Option::Option()
{
    code = "";
    label = "";
    price = 0.0f;
}

Option::Option(const string& c, const string& l, float p)
{
    setCode(c);
    setLabel(l);
    setPrice(p);
}

Option::Option(const Option& opt)
{
    code = opt.code;
    label = opt.label;
    price = opt.price;
}

//=============================================================================
// DESTRUCTEUR
//=============================================================================

Option::~Option()
{
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

string Option::toString() const
{
    stringstream ss;
    ss << fixed << setprecision(2);
    ss << "Code : " << code << endl;
    ss << "Intitule : " << label << endl;
    ss << "Prix : " << price << " euros";
    return ss.str();
}

//=============================================================================
// OPÉRATEURS D'INSERTION/EXTRACTION (FORMAT XML pour sérialisation)
//=============================================================================

ostream& operator<<(ostream& s, const Option& opt)
{
    s << "<Option>" << endl;
    s << "<code>" << endl;
    s << opt.code << endl;
    s << "</code>" << endl;
    s << "<label>" << endl;
    s << opt.label << endl;
    s << "</label>" << endl;
    s << "<price>" << endl;
    s << opt.price << endl;
    s << "</price>" << endl;
    s << "</Option>" << endl;
    
    return s;
}

istream& operator>>(istream& s, Option& opt)
{
    string line;
    
    // Lire <Option>
    getline(s, line);
    
    // Lire <code>
    getline(s, line);
    
    // Lire la valeur du code
    getline(s, line);
    opt.setCode(line);
    
    // Lire </code>
    getline(s, line);
    
    // Lire <label>
    getline(s, line);
    
    // Lire la valeur du label
    getline(s, line);
    opt.setLabel(line);
    
    // Lire </label>
    getline(s, line);
    
    // Lire <price>
    getline(s, line);
    
    // Lire la valeur du prix
    getline(s, line);
    opt.setPrice(stof(line));
    
    // Lire </price>
    getline(s, line);
    
    // Lire </Option>
    getline(s, line);
    
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
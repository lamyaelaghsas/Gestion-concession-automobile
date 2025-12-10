#include "Option.h"
#include <iostream>
#include <iomanip>

using namespace std;

namespace carconfig {

// Constructeur par défaut
Option::Option()
{
    code = "";
    label = "";
    price = 0.0f;
}

// Constructeur d'initialisation
Option::Option(const string& c, const string& l, float p)
{
    setCode(c);
    setLabel(l);
    setPrice(p);
}

// Constructeur de copie
Option::Option(const Option& opt)
{
    code = opt.code;
    label = opt.label;
    price = opt.price;
}

// Destructeur
Option::~Option()
{
}

// Getters
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

// Setters
void Option::setCode(const string& c)
{
    if(c.length() > 4 || c.length() < 4) 
        return;

    code = c;
}

void Option::setLabel(const string& l)
{
    label = l;
}

void Option::setPrice(float p)
{
    price = p;
}

// Affichage
void Option::display() const
{
    cout << "Code : " << code << endl;
    cout << "Intitule : " << label << endl;
    cout << fixed << setprecision(2);
    cout << "Prix : " << price << endl;
}

} // namespace carconfig
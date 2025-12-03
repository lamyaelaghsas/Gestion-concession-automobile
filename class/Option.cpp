#include "Option.h"
#include <iostream>
#include <iomanip>

using namespace std;

namespace carconfig {

// Constructeur par défaut
Option::Option()
{
    cout << "Option: Constructeur par defaut" << endl;
    code = "";
    label = "";
    price = 0.0f;
}

// Constructeur d'initialisation
Option::Option(const string& c, const string& l, float p)
{
    cout << "Option: Constructeur d'initialisation" << endl;
    setCode(c);
    setLabel(l);
    setPrice(p);
}

// Constructeur de copie
Option::Option(const Option& opt)
{
    cout << "Option: Constructeur de copie" << endl;
    code = opt.code;
    label = opt.label;
    price = opt.price;
}

// Destructeur
Option::~Option()
{
    cout << "Option: Destructeur" << endl;
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

ostream& operator<<(ostream& s, const Option& opt)
{
    s << "Code : " << opt.code << endl;
    s << "Intitule : " << opt.label << endl;
    s << fixed << setprecision(2);
    s << "Prix : " << opt.price << endl;
    return s;
}

} // namespace carconfig
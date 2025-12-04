#include "Employee.h"
#include <iostream>
#include <cctype>

using namespace std;

namespace carconfig {

// Initialisation des constantes statiques
const string Employee::ADMINISTRATIVE = "Administratif";
const string Employee::SELLER = "Vendeur";

//=============================================================================
// CONSTRUCTEURS
//=============================================================================

Employee::Employee() : Actor()
{
    cout << "Employee: Constructeur par defaut" << endl;
    setLogin("pas de login");
    password = nullptr;
    setRole("Vendeur");
}

Employee::Employee(const string& lastName, const string& firstName, int id,
                   const string& login, const string& role) 
    : Actor(lastName, firstName, id)
{
    cout << "Employee: Constructeur d'initialisation" << endl;
    password = nullptr;
    setLogin(login);
    setRole(role);
}

Employee::Employee(const Employee& e) : Actor(e)
{
    cout << "Employee: Constructeur de copie" << endl;
    password = nullptr;
    
    setLogin(e.getLogin());
    
    if (e.password != nullptr)
    {
        setPassword(e.getPassword());
    }
    
    setRole(e.getRole());
}

//=============================================================================
// DESTRUCTEUR
//=============================================================================

Employee::~Employee()
{
    cout << "Employee: Destructeur" << endl;
    if (password != nullptr)
    {
        delete password;
    }
}

//=============================================================================
// SETTERS
//=============================================================================

void Employee::setLogin(const string& login)
{
    this->login = login;
}

void Employee::setPassword(const string& pwd)
{
    // Vérification : minimum 6 caractères
    if (pwd.length() < 6)
    {
        cout << "Erreur: Mot de passe trop court (minimum 6 caracteres)" << endl;
        return;
    }
    
    // Vérification : contient au moins un chiffre
    bool hasDigit = false;
    for (size_t i = 0; i < pwd.length(); i++)
    {
        if (isdigit(pwd[i]))
        {
            hasDigit = true;
            break;
        }
    }
    
    if (!hasDigit)
    {
        cout << "Erreur: Le mot de passe doit contenir au moins un chiffre" << endl;
        return;
    }
    
    // Vérification : contient au moins une lettre
    bool hasAlpha = false;
    for (size_t i = 0; i < pwd.length(); i++)
    {
        if (isalpha(pwd[i]))
        {
            hasAlpha = true;
            break;
        }
    }
    
    if (!hasAlpha)
    {
        cout << "Erreur: Le mot de passe doit contenir au moins une lettre" << endl;
        return;
    }
    
    // Libérer l'ancien mot de passe s'il existe
    if (password != nullptr)
    {
        delete password;
    }
    
    // Créer le nouveau mot de passe
    password = new string(pwd);
}

void Employee::setRole(const string& role)
{
    if (role != "Vendeur" && role != "Administratif")
    {
        cout << "Erreur: Role invalide (doit etre Vendeur ou Administratif)" << endl;
        return;
    }
    this->role = role;
}

//=============================================================================
// GETTERS
//=============================================================================

string Employee::getLogin() const
{
    return login;
}

string Employee::getPassword() const
{
    if (password != nullptr)
    {
        return *password;
    }
    else
    {
        return "";
    }
}

string Employee::getRole() const
{
    return role;
}

//=============================================================================
// AFFICHAGE
//=============================================================================

void Employee::display() const
{
    cout << "EMPLOYEE:" << endl;
    cout << "Nom: " << getLastName() << endl;
    cout << "Prenom: " << getFirstName() << endl;
    cout << "ID: " << getId() << endl;
    cout << "Login: " << getLogin() << endl;
    if (password != nullptr)
    {
        cout << "MDP: " << getPassword() << endl;
    }
    cout << "Role: " << getRole() << endl;
}

//=============================================================================
// OPÉRATEURS
//=============================================================================

Employee& Employee::operator=(const Employee& e)
{
    Actor::operator=(e);
    
    setLogin(e.getLogin());
    
    if (e.password != nullptr)
    {
        setPassword(e.getPassword());
    }
    else
    {
        if (password != nullptr)
        {
            delete password;
        }
        password = nullptr;
    }
    
    setRole(e.getRole());
    
    return (*this);
}

ostream& operator<<(ostream& s, const Employee& e)
{
    s << "EMPLOYEE:" << endl;
    s << "Nom: " << e.getLastName() << endl;
    s << "Prenom: " << e.getFirstName() << endl;
    s << "ID: " << e.getId() << endl;
    s << "Login: " << e.getLogin() << endl;
    if (e.password != nullptr)
    {
        s << "MDP: " << e.getPassword() << endl;
    }
    s << "Role: " << e.getRole() << endl;
    return s;
}

//=============================================================================
// MÉTHODES VIRTUELLES
//=============================================================================

string Employee::tuple() const
{
    string str;
    str = to_string(getId()) + ";" + getLastName() + ";" + 
          getFirstName() + ";" + getRole();
    return str;
}

string Employee::toString() const
{
    string str;
    if (getRole() == "Vendeur")
    {
        str = "[S" + to_string(getId()) + "] " + getLastName() + " " + getFirstName();
    }
    else
    {
        str = "[A" + to_string(getId()) + "] " + getLastName() + " " + getFirstName();
    }
    return str;
}

//=============================================================================
// MÉTHODE SPÉCIFIQUE
//=============================================================================

void Employee::resetPassword()
{
    if (password == nullptr)
    {
        return;
    }
    
    delete password;
    password = nullptr;
}

} // namespace carconfig
#include "../includes/Employee.h"
#include "PasswordException.h"
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
    setLogin("pas de login");
    password = nullptr;
    setRole("Vendeur");
}

Employee::Employee(const string& lastName, const string& firstName, int id,
                   const string& login, const string& role) 
    : Actor(lastName, firstName, id)
{
    password = nullptr;
    setLogin(login);
    setRole(role);
}

Employee::Employee(const Employee& e) : Actor(e)
{
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
        throw PasswordException("Mot de passe trop court (minimum 6 caracteres)", PasswordException::INVALID_LENGTH);
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
        throw PasswordException("Le mot de passe doit contenir au moins un chiffre", PasswordException::DIGIT_MISSING);
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
        throw PasswordException("Le mot de passe doit contenir au moins une lettre", PasswordException::ALPHA_MISSING);
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
    if (password == nullptr)
    {
        throw PasswordException("Pas de mot de passe pour cet employe", PasswordException::NO_PASSWORD);
    }
    return *password;
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
    // Sérialisation XML (PAS de mot de passe dans le XML !)
    s << "<Employee>" << endl;
    s << "<lastName>" << endl;
    s << e.getLastName() << endl;
    s << "</lastName>" << endl;
    s << "<firstName>" << endl;
    s << e.getFirstName() << endl;
    s << "</firstName>" << endl;
    s << "<id>" << endl;
    s << e.getId() << endl;
    s << "</id>" << endl;
    s << "<login>" << endl;
    s << e.getLogin() << endl;
    s << "</login>" << endl;
    s << "<role>" << endl;
    s << e.getRole() << endl;
    s << "</role>" << endl;
    s << "</Employee>" << endl;
    
    return s;
}

istream& operator>>(istream& s, Employee& e)
{
    string line;
    
    // <Employee>
    getline(s, line);
    
    // <lastName>
    getline(s, line);
    // valeur
    getline(s, line);
    string lastName = line;
    // </lastName>
    getline(s, line);
    
    // <firstName>
    getline(s, line);
    // valeur
    getline(s, line);
    string firstName = line;
    // </firstName>
    getline(s, line);
    
    // <id>
    getline(s, line);
    // valeur
    getline(s, line);
    int id = stoi(line);
    // </id>
    getline(s, line);
    
    // <login>
    getline(s, line);
    // valeur
    getline(s, line);
    string login = line;
    // </login>
    getline(s, line);
    
    // <role>
    getline(s, line);
    // valeur
    getline(s, line);
    string role = line;
    // </role>
    getline(s, line);
    
    // </Employee>
    getline(s, line);
    
    // Créer l'employé
    e.setLastName(lastName);
    e.setFirstName(firstName);
    e.setId(id);
    e.setLogin(login);
    e.setRole(role);
    
    return s;
}

// Opérateur de comparaison pour set<Employee> (tri alphabétique par nom)
bool Employee::operator<(const Employee& e) const {
    return getLastName() < e.getLastName();
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
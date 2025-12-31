#include "../includes/Contract.h"

namespace carconfig {

//=============================================================================
// CONSTRUCTEURS
//=============================================================================

Contract::Contract() {
    id = 0;
    sellerId = 0;
    clientId = 0;
    carProjectName = "";
}

Contract::Contract(int id, int sellerId, int clientId, const string& carProjectName) {
    this->id = id;
    this->sellerId = sellerId;
    this->clientId = clientId;
    this->carProjectName = carProjectName;
}

Contract::Contract(const Contract& c) {
    id = c.id;
    sellerId = c.sellerId;
    clientId = c.clientId;
    carProjectName = c.carProjectName;
}

//=============================================================================
// DESTRUCTEUR
//=============================================================================

Contract::~Contract() {
    // Rien à libérer
}

//=============================================================================
// GETTERS
//=============================================================================

int Contract::getId() const {
    return id;
}

int Contract::getSellerId() const {
    return sellerId;
}

int Contract::getClientId() const {
    return clientId;
}

string Contract::getCarProjectName() const {
    return carProjectName;
}

//=============================================================================
// SETTERS
//=============================================================================

void Contract::setId(int id) {
    this->id = id;
}

void Contract::setSellerId(int sellerId) {
    this->sellerId = sellerId;
}

void Contract::setClientId(int clientId) {
    this->clientId = clientId;
}

void Contract::setCarProjectName(const string& name) {
    this->carProjectName = name;
}

//=============================================================================
// OPÉRATEUR D'AFFECTATION
//=============================================================================

Contract& Contract::operator=(const Contract& c) {
    if (this != &c) {
        id = c.id;
        sellerId = c.sellerId;
        clientId = c.clientId;
        carProjectName = c.carProjectName;
    }
    return *this;
}

//=============================================================================
// MÉTHODE TUPLE (pour la table)
//=============================================================================

string Contract::tuple() const {
    // Format : id;sellerId;clientId;carProjectName
    // Note: On retourne les IDs, pas les noms complets
    // L'interface graphique devra faire la correspondance
    return to_string(id) + ";" + 
           to_string(sellerId) + ";" + 
           to_string(clientId) + ";" + 
           carProjectName;
}

//=============================================================================
// AFFICHAGE
//=============================================================================

void Contract::display() const {
    cout << "Contract #" << id << endl;
    cout << "Seller ID: " << sellerId << endl;
    cout << "Client ID: " << clientId << endl;
    cout << "Car Project: " << carProjectName << endl;
}

//=============================================================================
// OPÉRATEURS DE FLUX (sérialisation XML)
//=============================================================================

ostream& operator<<(ostream& s, const Contract& c) {
    s << "<Contract>" << endl;
    s << "<id>" << endl;
    s << c.getId() << endl;
    s << "</id>" << endl;
    s << "<sellerId>" << endl;
    s << c.getSellerId() << endl;
    s << "</sellerId>" << endl;
    s << "<clientId>" << endl;
    s << c.getClientId() << endl;
    s << "</clientId>" << endl;
    s << "<carProjectName>" << endl;
    s << c.getCarProjectName() << endl;
    s << "</carProjectName>" << endl;
    s << "</Contract>" << endl;
    
    return s;
}

istream& operator>>(istream& s, Contract& c) {
    string line;
    
    // <Contract>
    getline(s, line);
    
    // <id>
    getline(s, line);
    // valeur
    getline(s, line);
    int id = stoi(line);
    // </id>
    getline(s, line);
    
    // <sellerId>
    getline(s, line);
    // valeur
    getline(s, line);
    int sellerId = stoi(line);
    // </sellerId>
    getline(s, line);
    
    // <clientId>
    getline(s, line);
    // valeur
    getline(s, line);
    int clientId = stoi(line);
    // </clientId>
    getline(s, line);
    
    // <carProjectName>
    getline(s, line);
    // valeur
    getline(s, line);
    string carProjectName = line;
    // </carProjectName>
    getline(s, line);
    
    // </Contract>
    getline(s, line);
    
    // Affecter les valeurs
    c.setId(id);
    c.setSellerId(sellerId);
    c.setClientId(clientId);
    c.setCarProjectName(carProjectName);
    
    return s;
}

} // namespace carconfig
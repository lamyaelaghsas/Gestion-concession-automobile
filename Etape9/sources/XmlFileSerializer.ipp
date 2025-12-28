#ifndef XMLFILESERIALIZER_IPP
#define XMLFILESERIALIZER_IPP

#include <iostream>

namespace carconfig {

// Constructeur
template <typename T>
XmlFileSerializer<T>::XmlFileSerializer(const string& fn, char m, const string& cn)
    : filename(fn), mode(m), collectionName(cn) {
    
    if (mode == WRITE) {
        file.open(filename, ios::out);
        if (!file.is_open()) {
            throw XmlFileSerializerException("Impossible d'ouvrir le fichier", XmlFileSerializerException::FILE_NOT_FOUND);
        }
        file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
        file << "<" << collectionName << ">" << endl;
    }
    else if (mode == READ) {
        file.open(filename, ios::in);
        if (!file.is_open()) {
            throw XmlFileSerializerException("Fichier introuvable", XmlFileSerializerException::FILE_NOT_FOUND);
        }
        
        string line;
        getline(file, line);  // <?xml...>
        getline(file, line);  // <collectionName>
        
        if (line.size() >= 3 && line.front() == '<' && line.back() == '>') {
            collectionName = line.substr(1, line.length() - 2);
        }
    }
}

// Destructeur
template <typename T>
XmlFileSerializer<T>::~XmlFileSerializer() {
    if (mode == WRITE && file.is_open()) {
        file << "</" << collectionName << ">" << endl;
    }
    if (file.is_open()) {
        file.close();
    }
}

// Méthode write - TOUJOURS avec endl
template <typename T>
void XmlFileSerializer<T>::write(const T& val) {
    if (mode != WRITE) {
        throw XmlFileSerializerException("Écriture non autorisée", XmlFileSerializerException::NOT_ALLOWED);
    }
    file << val << endl;  // ← TOUJOURS avec endl
}

// Méthode read - Version simple et robuste
template <typename T>
T XmlFileSerializer<T>::read() {
    if (mode != READ) {
        throw XmlFileSerializerException("Lecture non autorisée", XmlFileSerializerException::NOT_ALLOWED);
    }
    
    string line;
    T val;
    
    // Lire jusqu'à trouver une ligne non-vide
    do {
        streampos pos = file.tellg();
        getline(file, line);
        
        // Nettoyer
        size_t start = line.find_first_not_of(" \t\r\n");
        if (start != string::npos) {
            size_t end = line.find_last_not_of(" \t\r\n");
            line = line.substr(start, end - start + 1);
        } else {
            line = "";
        }
        
        // Si c'est la balise de fin
        if (line == "</" + collectionName + ">") {
            throw XmlFileSerializerException("Fin de fichier", XmlFileSerializerException::END_OF_FILE);
        }
        
        // Si on a une ligne valide, revenir et lire l'objet
        if (!line.empty()) {
            file.seekg(pos);
            file >> val;
            // Consommer le reste de la ligne
            getline(file, line);
            return val;
        }
    } while (!file.eof());
    
    throw XmlFileSerializerException("Fin de fichier", XmlFileSerializerException::END_OF_FILE);
}

// Accesseurs
template <typename T>
string XmlFileSerializer<T>::getFilename() const {
    return filename;
}

template <typename T>
string XmlFileSerializer<T>::getCollectionName() const {
    return collectionName;
}

template <typename T>
bool XmlFileSerializer<T>::isReadable() const {
    return mode == READ;
}

template <typename T>
bool XmlFileSerializer<T>::isWritable() const {
    return mode == WRITE;
}

} // namespace carconfig

#endif

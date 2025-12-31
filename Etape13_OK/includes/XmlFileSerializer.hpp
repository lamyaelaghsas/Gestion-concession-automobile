#ifndef XMLFILESERIALIZER_HPP
#define XMLFILESERIALIZER_HPP

#include "XmlFileSerializerException.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

namespace carconfig {

template<typename T>
class XmlFileSerializer
{
private:
    fstream file;
    string filename;
    char mode;
    string collectionName;

public: 
    // Constructeurs supprimés pour éviter les ouvertures multiples
    XmlFileSerializer() = delete;
    XmlFileSerializer(const XmlFileSerializer& fs) = delete;
    XmlFileSerializer<T>& operator=(const XmlFileSerializer<T>&) = delete;
    
    // Constructeur principal
    XmlFileSerializer(const string& fn, char m, const string& cn = "entities");
    
    // Destructeur
    ~XmlFileSerializer();
    
    // Accesseurs
    string getFilename() const;
    string getCollectionName() const;
    bool isReadable() const;
    bool isWritable() const;
    
    // Méthodes de sérialisation
    void write(const T& val);  // Sérialiser et écrire un objet dans le fichier
    T read();                   // Lire et désérialiser un objet à partir du fichier
    
    // Constantes statiques
    static const char READ;
    static const char WRITE;
};

// Définition des constantes statiques
template <typename T>
const char XmlFileSerializer<T>::READ = 'R';

template <typename T>
const char XmlFileSerializer<T>::WRITE = 'W';

} // namespace carconfig

#include "XmlFileSerializer.ipp"

#endif // XMLFILESERIALIZER_HPP
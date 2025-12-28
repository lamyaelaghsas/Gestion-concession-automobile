#ifndef XMLFILESERIALIZEREXCEPTION_H
#define XMLFILESERIALIZEREXCEPTION_H

#include "Exception.h"
#include <string>

using namespace std;

namespace carconfig {

class XmlFileSerializerException : public Exception
{
private:
    int code;
    
public:
    // Constantes statiques pour les codes d'erreur
    static const int NOT_ALLOWED = 1;
    static const int FILE_NOT_FOUND = 2;
    static const int END_OF_FILE = 3;
    
    // Constructeurs
    XmlFileSerializerException();
    XmlFileSerializerException(const string& message, int code);
    XmlFileSerializerException(const XmlFileSerializerException& e);
    
    // Destructeur
    virtual ~XmlFileSerializerException();
    
    // Setters
    void setCode(int code);
    
    // Getters
    int getCode() const;
    
    // Opérateurs
    XmlFileSerializerException& operator=(const XmlFileSerializerException& e);
};

} // namespace carconfig

#endif
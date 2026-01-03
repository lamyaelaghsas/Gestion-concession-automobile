#include "../includes/XmlFileSerializerException.h"

using namespace std;

namespace carconfig {

// Initialisation des constantes statiques
const int XmlFileSerializerException::NOT_ALLOWED;
const int XmlFileSerializerException::FILE_NOT_FOUND;
const int XmlFileSerializerException::END_OF_FILE;

//=============================================================================
// CONSTRUCTEURS
//=============================================================================

XmlFileSerializerException::XmlFileSerializerException() : Exception("Erreur XmlFileSerializer")
{
    setCode(0);
}

XmlFileSerializerException::XmlFileSerializerException(const string& message, int code) : Exception(message)
{
    setCode(code);
}

XmlFileSerializerException::XmlFileSerializerException(const XmlFileSerializerException& e) : Exception(e)
{
    setCode(e.getCode());
}

//=============================================================================
// DESTRUCTEUR
//=============================================================================

XmlFileSerializerException::~XmlFileSerializerException()
{
}

//=============================================================================
// SETTERS
//=============================================================================

void XmlFileSerializerException::setCode(int code)
{
    this->code = code;
}

//=============================================================================
// GETTERS
//=============================================================================

int XmlFileSerializerException::getCode() const
{
    return code;
}

//=============================================================================
// OPÉRATEURS
//=============================================================================

XmlFileSerializerException& XmlFileSerializerException::operator=(const XmlFileSerializerException& e)
{
    Exception::operator=(e);
    setCode(e.getCode());
    return (*this);
}

} // namespace carconfig
#ifndef BODYTEXTPARSER_H
#define BODYTEXTPARSER_H

#include <string>
#include <stdlib.h>   // pour strncpy_s
#include <Expat/include/expat.h>

/** ****************************************************************************
 * @brief La classe \b statique BodyTextParser analyse le Body XML d'un message,
 *        pour l'afficher sous forme de texte simple dans l'onglet "Text View".
 *
 * Elle sert à convertir un blob XML (typiquement le body d'un message SOAP)
 * en un XML contenant des balises de coloration syntaxique pour un affichage dans QT.
 * Le parser SAX est basé sur la librarie EXPAT.
 *
 * @author David de Lorenzo
 **************************************************************************** */
class BodyTextParser
{
public:
    static int  parse(std::string blob, bool hideNamespaces);
    static int  parse(char* buffer, bool hideNamespaces);
    static std::string  getFormatedBlob();

    // Methodes statiques du Parser
    static void XMLCALL startElementHandler(void *userData, const XML_Char *name, const XML_Char **attrs);
    static void XMLCALL endElementHandler(void *userData, const XML_Char *name);
    static void XMLCALL commentHandler(void *userData, const XML_Char *data);
    static void XMLCALL dataHandler(void *userData, const XML_Char *content, int length);

private:
    static const long  MAX_BODY_SIZE = 1024*512;       ///< 512kB : Taille max des Body (il y a une limitation dans Expat)
    static int         profondeur;
    static bool        elementClosed;
    static bool        keepNamespaces;
    static std::string formatedBlob;
    static std::string errMessage;

};

#endif // BODYTEXTPARSER_H

#ifndef __CODIGOGENETICO__H__
#define __CODIGOGENETICO__H__
#include "Cadena.h"
#include "ArbolHuffman.h"
using namespace std;

class CompareNode
{
    public:
    bool operator()(NodoHuffman* n, NodoHuffman* n2) const // Returns true if t1 is earlier than t2
    {
        if(n->frecuencia > n2->frecuencia)
        {
            return true;//(n->frecuencia > n2->frecuencia);
        }
        if(n->frecuencia == n2->frecuencia)
        {
            if(n->caracter > n2->caracter)
            {
                return true;
            }
            return false;
        }
       return false;//(n->frecuencia < n2->frecuencia);
    }
};



class CodigoGenetico {
  public:
    CodigoGenetico();
    vector < Cadena > getListaCadenas();
    map < char , long long > getBasesTotales();
    int contarSecuencias();
    bool cargarDatos(string);
    void listaSecuencias();
    string findCode(NodoHuffman*, char, string);
    Cadena* buscarCadena(string);
    void mostrarHistograma(string);
    bool guardarDatos(string);
    int subCadenas(string , bool );
    ArbolHuffman* generarArbol();
    bool encode( string );
    bool decode( string );
  protected:
    vector < Cadena > listaCadenas;
    map < char , long long > basesTotales;
    ArbolHuffman* tree;
};

#include "CodigoGenetico.hxx"

#endif //

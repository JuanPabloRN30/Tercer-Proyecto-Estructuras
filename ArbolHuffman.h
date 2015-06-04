#ifndef ArbolHuffman_H_INCLUDED
#define ArbolHuffman_H_INCLUDED

#include "NodoHuffman.h"

class ArbolHuffman
{
public:
    NodoHuffman* raiz;
    ArbolHuffman();
    ArbolHuffman(NodoHuffman* nraiz);
    ~ArbolHuffman();
    NodoHuffman* getRaiz();
    void setRaiz(NodoHuffman*);
};

#include "ArbolHuffman.hxx"

#endif // ARBOLBINARIO_H_INCLUDED


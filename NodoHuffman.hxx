#ifndef NodoHuffman_HXX_INCLUDED
#define NodoHuffman_HXX_INCLUDED

NodoHuffman::NodoHuffman()
{

}

NodoHuffman::~NodoHuffman()
{

}

NodoHuffman::NodoHuffman(unsigned long long int f,unsigned char d)
{
    frecuencia = f;
    caracter = d;
    izq = NULL;
    der = NULL;
}

NodoHuffman::NodoHuffman(NodoHuffman* nIzq, NodoHuffman* nDer)
{
    NodoHuffman* padre = new NodoHuffman((nDer->frecuencia + nIzq->frecuencia),'@');
    padre->setDerecha(nDer);
    padre->setIzquierda(nIzq);
}

void NodoHuffman::setFrecuencia(unsigned long long int f)
{
    frecuencia = f;
}

unsigned long long int NodoHuffman::getFrecuencia()
{
    return frecuencia;
}

void NodoHuffman::setCaracter(unsigned char c)
{
    caracter = c;
}

unsigned char NodoHuffman::getCaracter()
{
    return caracter;
}

NodoHuffman* NodoHuffman::getDerecha()
{
    return der;
}


NodoHuffman* NodoHuffman::getIzquierda()
{
    return izq;
}


void NodoHuffman::setDerecha(NodoHuffman* nderecha)
{
    der = nderecha;
}


void NodoHuffman::setIzquierda(NodoHuffman* nizquierda)
{
    izq = nizquierda;
}

string NodoHuffman::buscar(unsigned char c)
{
/*    if(c != '@')
    {
        if(izq != NULL)
        {

        }
        return true;
    }
    else
    {
        return;
    }*/
}

bool NodoHuffman::IsLeaf( )
{
    return (izq == NULL && der == NULL);
}

#endif // NodoHuffman_HXX_INCLUDED


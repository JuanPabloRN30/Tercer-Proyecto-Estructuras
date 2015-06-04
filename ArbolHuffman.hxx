#ifndef ArbolHuffman_HXX_INCLUDED
#define ArbolHuffman_HXX_INCLUDED

ArbolHuffman::ArbolHuffman()
{

}

ArbolHuffman::ArbolHuffman(NodoHuffman* nraiz)
{
    raiz = nraiz;
}

ArbolHuffman::~ArbolHuffman()
{

}

NodoHuffman* ArbolHuffman::getRaiz()
{
    return raiz;
}

void ArbolHuffman::setRaiz(NodoHuffman* nraiz)
{
    raiz = nraiz;
}

#endif // ARBOLBINARIO_HXX_INCLUDED


CodigoGenetico::CodigoGenetico()
{
}

vector < Cadena > CodigoGenetico::getListaCadenas()
{
    return listaCadenas;
}

map < char , long long > CodigoGenetico::getBasesTotales()
{
    return basesTotales;
}

bool CodigoGenetico::cargarDatos(string nombreArchivo)
{
    ifstream entrada;
    bool bandera = false;
    entrada.open(nombreArchivo.c_str(),ios::in);
    if(!entrada)
        return false;
    string tipo;
    getline(entrada,tipo);
    map < char , int > mapa;
    while(!entrada.eof() && !bandera)
    {
        string cadena,cadTot;
        cadena = cadTot = "";
        while(cadena[0] != '>' && !bandera)
        {
            cadTot+= cadena;
            getline(entrada,cadena);
            if(cadena[0] != '>')
                cadena+='\n';
            if(entrada.eof())
                bandera = true;

        }
        bool bandera,bandera1;
        int cont,cont1;
        bandera = bandera1 = true;
        cont = cont1 = 0;
        for(int j = 0 ; j < cadTot.size(); j++)
        {
            if(cadTot[j] != '\n')
            {
                mapa[cadTot[j]]++;
                basesTotales[cadTot[j]]++;
                cont++;
            }
            else
            {
                bandera1 = false;
            }
            if(bandera1)
                cont1++;
            if(cadTot[j] == '-')
            {
                bandera = false;
            }

        }
        Cadena cad(tipo.substr(1,tipo.size()-1),cadTot,cont,cont1,bandera,mapa);
        mapa.clear();
        listaCadenas.push_back(cad);
        tipo = cadena;
    }
    tree = generarArbol();
    entrada.close();
    return true;
}

int CodigoGenetico::contarSecuencias()
{
    return listaCadenas.size();
}

ArbolHuffman* CodigoGenetico::generarArbol()
{
    priority_queue<NodoHuffman*, vector<NodoHuffman*>, CompareNode > pq;
    map<char,long long >::iterator it;
    for(it = basesTotales.begin() ; it != basesTotales.end() ; it++)
    {
        pq.push(new NodoHuffman(it->second,it->first));
    }
    if(pq.size() != 1)
    {
        while(pq.size() != 2)
        {
            NodoHuffman* t1 = pq.top();
            pq.pop();
            NodoHuffman* t2 = pq.top();
            pq.pop();
            NodoHuffman* padre = new NodoHuffman();
            padre->izq = t1;
            padre->der = t2;
            padre->frecuencia = t1->frecuencia + t2->frecuencia;
            padre->caracter = '1';
            pq.push(padre);
        }
        NodoHuffman* t1 = pq.top();
        pq.pop();
        NodoHuffman* t2 = pq.top();
        pq.pop();
        NodoHuffman* padre = new NodoHuffman();
        padre->izq = t1;
        padre->der = t2;
        padre->frecuencia = t1->frecuencia + t2->frecuencia;
        padre->caracter = '1';
        ArbolHuffman* arbol = new ArbolHuffman(padre);
        return arbol;
    }
    else
    {
        return NULL;
    }
}

void CodigoGenetico::listaSecuencias()
{
    for(int i = 0 ; i < contarSecuencias() ; i++)
    {
        Cadena c = listaCadenas[i];
        string tipo = c.getTipo();
        int cantBases = c.getTam();
        printf("Secuencia: %s",tipo.c_str());
        if(c.isComplete())
            printf(" tiene %d bases\n",cantBases);
        else
            printf(" tiene al menos %d bases\n",cantBases);
    }
}

Cadena* CodigoGenetico::buscarCadena(string descripcion)
{
    Cadena* cad = NULL;
    for(int i = 0 ; i < contarSecuencias() ; i++)
    {
        if(listaCadenas[i].getTipo() == descripcion)
        {
            cad = new Cadena(listaCadenas[i].getTipo(),listaCadenas[i].getCadena(),listaCadenas[i].getTam(),listaCadenas[i].getIdent(),listaCadenas[i].isComplete(),listaCadenas[i].getBases());
        }
    }
    return cad;

}

bool CodigoGenetico::guardarDatos(string nombreArchivo)
{
    ofstream salida;
    salida.open(nombreArchivo.c_str(),ios::out);
    for(int i = 0 ; i < listaCadenas.size() ; i++)
    {
        salida << ">" << listaCadenas[i].getTipo().c_str() << endl;
        salida << listaCadenas[i].getCadena().c_str();
    }
    if(salida.fail())
        return false;
    else
        return true;
}

void CodigoGenetico::mostrarHistograma(string descripcion)
{
    Cadena* cadena = buscarCadena(descripcion);
    if(cadena == NULL)
        cout << "Secuencia invalida" << endl;
    else
    {
        vector < char > bases = ingresarBases();
        for(int i = 0 ; i < bases.size() ; i++)
        {
            printf("%5c : %5d\n",bases[i],cadena->getBases().find(bases[i])->second);
        }

    }
}

int CodigoGenetico::subCadenas(string subCadena, bool bandera)
{
    int cant = 0;
    for(int i = 0 ; i < listaCadenas.size() ; i++)
        cant += listaCadenas[i].subCadenas(subCadena, bandera);

    return cant;
}


string CodigoGenetico::findCode(NodoHuffman* current, char objective, string code)
{
    if(current->izq == NULL && current->der == NULL)
    {
        if(current->caracter == objective)
        {
            return code;
        }
        else
        {
            return "";
        }
    }
    else
    {
        string res = findCode(current->izq,objective,code + "0");
        if(res == "")
        {
            return findCode(current->der,objective,code + "1");
        }
        else
        {
            return res;
        }
    }
}

bool CodigoGenetico::encode(string fileName)
{
    map < char , long long > id;
    map < char , long long >::iterator it;
    ofstream salida;
    salida.open(fileName.c_str(),ios::binary|ios::out);
    if(salida.fail())
    {
        salida.close();
        return false;
    }
    unsigned short int totalBases = (short unsigned int)basesTotales.size();
    salida.write(reinterpret_cast<char*> (&totalBases),sizeof(unsigned short int));
    long long consecutivo = 0;
    for(it = basesTotales.begin() ; it != basesTotales.end() ; it++)
    {
        if(id.find(it->first) == id.end())
        {
            id[it->first] = consecutivo;
            consecutivo++;
        }
        unsigned char caracter = it->first;
        unsigned long long int repeticiones = it->second;
        salida.write(reinterpret_cast<char*> (&caracter),sizeof(unsigned char));
        salida.write(reinterpret_cast<char*> (&repeticiones),sizeof(unsigned long long int));
    }

    unsigned int cantidadSecuencias = contarSecuencias();
    salida.write(reinterpret_cast<char*> (&cantidadSecuencias),sizeof(unsigned int));
    for(int i = 0 ; i < cantidadSecuencias ; i++)
    {
        unsigned short int tamTipoSec = listaCadenas[i].getTipo().size();
        salida.write(reinterpret_cast<char*> (&tamTipoSec),sizeof(unsigned short int));
        for(int j = 0 ; j < tamTipoSec ; j++)
        {
            salida.write(reinterpret_cast<char*> (&listaCadenas[i].getTipo()[j]),sizeof(unsigned char));
        }
    }

    long long cont = 0;
    string tot = "";
    vector < bool > already(totalBases,false);
    vector < string > codesOpt(totalBases);
    for(int i = 0 ; i < cantidadSecuencias ; i++)
    {
        unsigned long long int tamSecuencia = listaCadenas[i].getTam();
        salida.write(reinterpret_cast<char*> (&tamSecuencia),sizeof(unsigned long long int));
        unsigned short int ident = listaCadenas[i].getIdent();
        salida.write(reinterpret_cast<char*> (&ident),sizeof(unsigned short int));
        for(int j = 0 ; j < tamSecuencia ; j++)
        {
            if(listaCadenas[i].getCadena()[j] == '\n')
            {
                tamSecuencia++;
            }
            else
            {
                int actualId = id[listaCadenas[i].getCadena()[j]];
                if(!already[actualId])
                {
                    already[actualId] = true;
                    string code = "";
                    codesOpt[actualId] = findCode(tree->raiz,listaCadenas[i].getCadena()[j],code);
                }
                tot += codesOpt[actualId];
            }
        }
        long long tam = ceil((double)tot.size()/(double)8);
        unsigned char* c = new unsigned char[tam];
        int contAux = 0;
        int byteIndex = 0;
        c[byteIndex] = 0;
        long long rest = tot.size()%8;

        for(int i = 0  ; i < tot.size()-rest ; i++)
        {
            if(tot[i] == '1')
            {
                c[byteIndex] |= (1 << contAux);
            }
            contAux++;
            if(contAux%8 == 0)
            {
                contAux = 0;
                salida.write(reinterpret_cast<char*> (&c[byteIndex]),sizeof(unsigned char));
                byteIndex++;
                c[byteIndex] = 0;
            }
        }
        if(rest != 0)
        {
            char finish = 0;
            contAux = 0;
            for(int i = tot.size()-rest ; i < (tot.size()-rest) + 8 ; i++)
            {
                if(i < tot.size() && tot[i] == '1')
                {
                    finish |= (1 << contAux);
                }
                contAux++;
            }
            salida.write(reinterpret_cast<char*> (&finish),sizeof(unsigned char));
        }
        tot = "";
    }
    return true;
}


bool CodigoGenetico::decode(string fileName)
{
    map < char , long long >::iterator it;
    vector < Cadena > listaAuxiliar;
    ifstream entrada;
    entrada.open(fileName.c_str(),ios::binary|ios::in);
    if(entrada.fail())
        return false;
    entrada.seekg(0,ios::beg);
    unsigned short int totalBases;
    entrada.read((char*) &totalBases, sizeof(unsigned short int));
    for(int i = 0 ; i < totalBases ; i++)
    {

        char caracter;
        unsigned long long int frecuencia;
        entrada.read((char*) &caracter, sizeof(char));
        entrada.read((char*) &frecuencia, sizeof(unsigned long long int));
        basesTotales[caracter] = frecuencia;
    }
    tree = generarArbol();
    map < string , char > decodes;
    for(it = basesTotales.begin() ; it != basesTotales.end() ; it++)
    {
        string code = "";
        string res = findCode(tree->raiz,it->first,code);
        decodes[res] = it->first;
    }
    unsigned int cantidadSecuencias;
    entrada.read((char*) &cantidadSecuencias, sizeof(unsigned int));
    vector < string > tipos(cantidadSecuencias);
    for(int i = 0 ; i < cantidadSecuencias ; i++)
    {
        unsigned short int tamTipoSec;
        entrada.read((char*) &tamTipoSec, sizeof(unsigned short int));
        string tipoCadena = ">";
        for(int j = 0 ; j < tamTipoSec ; j++)
        {
            unsigned char aux;
            entrada.read((char*) &aux, sizeof(unsigned char));
            tipoCadena+= aux;
        }
        tipos[i] = tipoCadena;
    }

    long long cont = 0;
    string parcial = "";
    for(int i = 0 ; i < cantidadSecuencias ; i++)
    {
        unsigned long long int tamSecuencia;
        entrada.read((char*) &tamSecuencia, sizeof(unsigned long long int));
        unsigned short int ident;
        entrada.read((char*) &ident, sizeof(unsigned short int));
        unsigned char bits;
        int cont = 0;
        string parcial = "";
        string cadTot = "";
        int cont1 = 0;
        bool bandera = true;
        map < char , int > mapita;

        while(cont < tamSecuencia)
        {
            entrada.read((char*) &bits, 1);
            for(int j = 0 ; j < 8  && cont < tamSecuencia; j++)
            {
                if((bits&(1<<j)) != 0)
                {
                    parcial += "1";
                }
                else
                {
                    parcial += "0";
                }

                map < string , char >::iterator it3;
                it3 = decodes.find(parcial);
                if(it3 != decodes.end())
                {
                    if(cont%ident == 0 && cont != 0)
                    {
                        cadTot += '\n';
                    }
                    cadTot += it3->second;
                    if(it3->second == '-')
                        bandera = false;
                    mapita[it3->second]++;
                    parcial = "";
                    cont++;
                }
            }
        }
        cadTot += '\n';
        Cadena cad(tipos[i].substr(1,tipos[i].size()-1),cadTot,tamSecuencia,ident,bandera,mapita);
        listaAuxiliar.push_back(cad);
    }
    listaCadenas = listaAuxiliar;
    return true;
}

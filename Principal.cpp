#include<iostream>
#include<math.h>
#include <stdlib.h>
#include<vector>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<sstream>
#include<fstream>
#include "CodigoGenetico.h"
#include "Menu.h"
using namespace std;

CodigoGenetico cargar(string nombreArchivo)
{
    CodigoGenetico codigo;
    if(codigo.cargarDatos(nombreArchivo))
    {
        int diferencia = codigo.contarSecuencias();
        if(diferencia == 0)
            cout << nombreArchivo << " no contiene ninguna secuencia" << endl;
        else if(diferencia == 1)
            cout << 1 << " secuencia cargada cargada de: " << nombreArchivo << endl;
        else
            cout << diferencia << " secuencia cargada cargada de: " << nombreArchivo << endl;
        return codigo;
    }
    else
        cout << "ERROR CON EL ARCHIVO " << endl;
}

void contar(CodigoGenetico &codigo)
{
    int cantSecuencias = codigo.contarSecuencias();
    if(cantSecuencias == 0)
        cout << "No hay secuencias cargadas" << endl;
    else if(cantSecuencias == 1)
        cout << "1 secuencia cargada" << endl;
    else
        cout << cantSecuencias << " secuencias cargadas" << endl;
}

void listaSecuencias(CodigoGenetico &codigo)
{
    int cantSecuencias = codigo.contarSecuencias();
    if(cantSecuencias == 0)
        cout << "No hay secuencias cargadas" << endl;
    else
    {
        codigo.listaSecuencias();
    }
}

void subSecuencia(CodigoGenetico &codigo, string secuencia)
{
    int cantSecuencias = codigo.contarSecuencias();
    if(cantSecuencias == 0)
    {
        cout << "No hay secuencias cargadas" << endl;
    }
    else
    {
        int cantidad = codigo.subCadenas(secuencia,1);
        if(cantidad == 0)
            cout << "No existe esa subsecuencia" << endl;
        else
            cout << "La secuencia dada se repite: " << cantidad << " de veces." << endl;

    }
}

void mascara(CodigoGenetico &codigo, string secuencia )
{
    int cantSecuencias = codigo.contarSecuencias();
    if(cantSecuencias == 0)
        cout << "No hay secuencias cargadas" << endl;
    else
    {
        int cantidad = codigo.subCadenas(secuencia,0);
        if(cantidad == 0)
            cout << "No se enmascararon subsecuencias" << endl;
        else if(cantidad == 1)
            cout << "1 Subsecuencia se enmascaro" << endl;
        else
            cout << cantidad <<" Subsecuencias se enmascararon" << endl;
    }
}

void guardar(CodigoGenetico codigo, string nombreArchivo)
{
    int cantSecuencias = codigo.contarSecuencias();
    if(cantSecuencias == 0)
    {
        cout << "No hay secuencias cargadas" << endl;
    }
    else
    {
        if(codigo.guardarDatos(nombreArchivo))
            cout << "Las secuencias se guardaron correctamente en: " << nombreArchivo << endl;
        else
            cout << "Error escribiendo el archivo: " << nombreArchivo << endl;
    }
}

void encode(CodigoGenetico &codigo, string fileName)
{
    if(codigo.encode(fileName))
    {
        cout << "Se guardaron las secuencias en: " << fileName << endl;
    }
    else
    {
        cout << "No se logro guardar las secuencias en: " << fileName << endl;
    }
}

void decode(CodigoGenetico &codigo, string fileName)
{
    if(codigo.decode(fileName))
    {
        cout << "Se cargaron las secuencias de: " << fileName << endl;
    }
    else
    {
        cout << "No se logro cargar las secuencias de: " << fileName << endl;
    }
}

void shortest_path(CodigoGenetico &codigo, string sequence_Description, int i , int j , int x , int y)
{
    codigo.shortest_path(sequence_Description,i,j,x,y);
}

void remote_base(CodigoGenetico &codigo, string sequence_Description, int i , int j)
{
    codigo.remote_base(sequence_Description,i,j);
}

int main()
{
    CodigoGenetico codigo;
    string comando;
    int cantSecuencias;
    do
    {
        cout << "$ ";
        cin >> comando;
        if(comando == "help")
        {
            string opc2;
            cin >> opc2;
            if(opc2 == "load")
                load();
            else if(opc2 == "count")
                countM();
            else if(opc2 == "list_sequences")
                list_sequences();
            else if(opc2 == "histogram")
                histogram();
            else if(opc2 == "is_subsequence")
                is_subsequence();
            else if(opc2 == "mask")
                mask();
            else if(opc2 == "save")
                save();
            else if(opc2 == "encode")
                encode();
            else if(opc2 == "decode")
                decode();
            else if(opc2 == "shortest_path")
                shortest_path();
            else if(opc2 == "remote_base")
                remote_base();
        }
        else
        {
            if(comando == "load")
            {
                string fileName;
                cin.ignore();
                getline(cin,fileName);
                codigo = cargar(fileName);
            }
            else if(comando == "count")
            {
                contar(codigo);
            }
            else if(comando == "list_sequences")
            {
                listaSecuencias(codigo);
            }
            else if(comando == "histogram")
            {
                string sequence_description;
                cin.ignore();
                getline(cin,sequence_description);
                codigo.mostrarHistograma(sequence_description);
            }
            else if(comando == "is_subsequence")
            {
                string secuencia;
                cin.ignore();
                getline(cin,secuencia);
                subSecuencia(codigo,secuencia);
            }
            else if(comando == "mask")
            {
                string secuencia;
                cin.ignore();
                getline(cin,secuencia);
                mascara(codigo,secuencia);
            }
            else if(comando == "save")
            {
                string fileName;
                cin.ignore();
                getline(cin,fileName);
                guardar(codigo,fileName);
            }
            else if(comando == "encode")
            {
                string fileName;
                cin.ignore();
                getline(cin,fileName);
                encode(codigo,fileName);
            }
            else if(comando == "decode")
            {
                string fileName;
                cin.ignore();
                getline(cin,fileName);
                decode(codigo,fileName);
            }
            else if(comando == "shortest_path")
            {
                string line;
                cin.ignore();
                getline(cin,line);
                reverse(line.begin(),line.end());
                stringstream ss(line);
                vector < int > positions(4);
                string aux = "",sequenceDescription="";
                for(int i = 3 ; i >= 0 ; i--)
                {
                    ss >> aux;
                    reverse(aux.begin(),aux.end());
                    stringstream ss1(aux);
                    ss1 >> positions[i];
                }
                while(ss >> aux)
                {
                    reverse(aux.begin(),aux.end());
                    sequenceDescription = aux + " " +sequenceDescription ;
                }
                sequenceDescription.erase(sequenceDescription.size()-1);
                shortest_path(codigo,sequenceDescription,positions[0],positions[1],positions[2],positions[3]);
            }
            else if(comando == "remote_base")
            {
                string line;
                cin.ignore();
                getline(cin,line);
                reverse(line.begin(),line.end());
                stringstream ss(line);
                vector < int > positions(3);
                string aux = "",sequenceDescription="";
                for(int i = 1 ; i >= 0 ; i--)
                {
                    ss >> aux;
                    reverse(aux.begin(),aux.end());
                    stringstream ss1(aux);
                    ss1 >> positions[i];
                }
                while(ss >> aux)
                {
                    reverse(aux.begin(),aux.end());
                    sequenceDescription = aux + " " +sequenceDescription ;
                }
                sequenceDescription.erase(sequenceDescription.size()-1);
                cout << sequenceDescription << "   "<< positions[0] << " " << positions[1] << endl;
                remote_base(codigo,sequenceDescription,positions[0],positions[1]);
            }
        }
    }
    while(comando != "exit");
    return 0;
}

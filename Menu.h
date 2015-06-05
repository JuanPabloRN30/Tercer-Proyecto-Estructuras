void load()
{
    cout << "Escriba el comando: load <filename>" << endl;
    cout << "Carga en memoria los datos contenidos en el archivo identificado por <filename>." << endl;
}

void countM()
{
    cout << "Escriba el comando: count" << endl;
    cout << "Imprime por pantalla la cantidad de secuencias cargadas en memoria." << endl;
}

void list_sequences()
{
    cout << "Escriba el comando: list_sequences" << endl;
    cout << "Imprime en n líneas (una para secuencia) la informacion basica" << endl;
    cout << "(cantidad de bases) de cada secuencia." << endl;
}

void histogram()
{
    cout << "Escriba el comando: histogram <sequence_description>" << endl;
    cout << "Imprime el histograma de una secuencia, en caso de que exista. El histograma se define como";
    cout << " el conteo (frecuencia) de cada código en la secuencia." << endl;
}

void is_subsequence()
{
    cout << "Escriba el comando: is_subsequence <sequence>" << endl;
    cout << "Determina si una secuencia, dada por el usuario, existe dentro de las secuencias cargadas." << endl;
}

void mask()
{
    cout << "Escriba el comando: mask <sequence>" << endl;
    cout << "Enmascara una secuencia dada por el usuario, si existe. Los elementos que pertenecen a la";
    cout << "subsecuencia se enmascaran cambiando cada codigo por el codigo X." << endl;
}

void save()
{
    cout << "Escriba el comando: save <filename>" << endl;
    cout << "Guarda en el archivo <filename> las secuencias cargadas en memoria." << endl;;
    cout << "Se debe tener en cuenta la justificacion (de lineas) del archivo inicial." << endl;
}

void encode()
{
    cout << "Escriba el comando encode <filename.fabin>" << endl;
    cout << "El comando debe generar el archivo binario con la correspondiente codificacion de Huffman," << endl;
    cout << "almacenandolo en disco bajo el nombre <filename.fabin>" << endl;
}

void decode()
{
    cout << "Escriba el comando decode <filename.fabin>" << endl;
    cout << "El comando debe cargar en memoria las secuencias contenidas en el archivo binario <filename.fabin>," << endl;
    cout << "que contiene una codificacion Huffman de un conjunto de secuencias." << endl;
}

void shortest_path()
{
    cout << "Escriba el comando shortest_path <sequence_description> <i> <j> <x> <y>" << endl;
    cout << "El comando debe imprimir en pantalla la secuencia de vertices del grafo que describen la ruta " << endl;
    cout << "mas corta entre la base ubicada en la posicion [i,j] de la matriz de la secuencia <sequence_description> " << endl;
    cout << "y la base ubicada en la posicion [x,y] de la misma matriz.Asi mismo, debe imprimir el costo total de la " << endl;
    cout << "ruta, teniendo en cuenta el peso que tiene cada conexion entre bases." << endl;
}

void remote_base()
{
    cout << "Escriba el comando remote_base <sequence_description> <i> <j>" << endl;
    cout << "Para la base ubicada en la posición [i,j] de la matriz de la secuencia <sequence_description>, " << endl;
    cout << "el comando busca la ubicacion de la misma base (misma letra) mas lejana dentro de la matriz. Para esta " << endl;
    cout << "base remota, el comando debe imprimir en pantalla su ubicacion, la secuencia de vertices que describen la " << endl;
    cout << "ruta entre la base origen y la base remota, y el costo total de la ruta." << endl;
}

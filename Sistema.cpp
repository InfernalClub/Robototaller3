#include "Sistema.h"

void Sistema::lecturaArchivo()
{
    ifstream archivo("laberinto.txt");
    string linea;

    //En caso de que la lectura falle
    if (archivo.fail())
    {
        cout << "El archivo no se puede leer" << endl;
        exit(1);
    }

    // Leer el archivo línea por línea
    while (!archivo.eof()) {
        getline(archivo, linea);
        vector<char> fila;

        // Leer cada caracter de la línea y agregarlo a la fila
        for (char c : linea) {
            fila.push_back(c);
        }

        // Agregar la fila al laberinto
        laberinto.push_back(fila);
    }

    // Imprimir la matriz de caracteres
    for (const auto& fila : laberinto) {
        for (char c : fila) {
            cout << c << " ";
        }
        cout << endl;
    }
    archivo.close();
}


void Sistema::comprobarPosicion(int fila, int columna)
{

    if (laberinto [fila][columna] == '#') {
        cout << "¡Error! Casilla del tipo pared" << endl;
        return;
    }
    else if (fila >= 0 && fila < laberinto.size() && columna >= 0 && columna < laberinto[fila].size())
    {
        char elemento = laberinto[fila][columna];
        cout << "Se ha ingresado correctamente la cordenada" << endl;
        return;
    }
    else 
    {
        cout << "¡Error! Casilla invalida" << endl;
        return;
    }
}

void Sistema::Menu()
{
    lecturaArchivo();
    cout << "Hola ingresa unas cordenadas: " << endl;
    cin >> fila;
    cin >> columna;
    comprobarPosicion(fila, columna);

}

#include "Sistema.h"

void Sistema::lecturaArchivo()
{
    ifstream archivo("laberinto.txt");
    vector<vector<char>> laberinto;
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

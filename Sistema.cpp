#include "Sistema.h"

vector<vector<char>> Sistema::leerLaberinto()
{
	ifstream archivo ("laberinto.txt");

	if (archivo.is_open()) 
	{
		string linea;
		while (getline(archivo, linea))
		{
			vector <char> fila;
			for (char c : linea) {
				if (c == '#' || c == ' ') {
					fila.push_back(c);
				}
			}
			this->laberinto.push_back(fila);
		}

		for (const auto& fila : this->laberinto) {
			for (char c : fila) {
				cout << c << " ";
			}
			cout << endl;
		}

		archivo.close();
	}
	else
	{
		cout << "No se pudo abrir el archivo." << endl;
	}
	return laberinto;
}

bool Sistema::verificarPosicion(const vector<vector<char>>& laberinto, int fila, int columna)
{
	if (isdigit(fila) || isdigit(columna)) {
		cout << "Error: Los valores de fila y columna deben ser enteros." << endl;
		return false;
	}
	// Verificar los límites de la matriz
	if (fila < 0 || fila >= laberinto.size() || columna < 0 || columna >= laberinto[fila].size()) {
		cout << "Error: La posicion ingresada esta fuera de los limites del laberinto." << endl;
		return false;
	}
	// Verificar el contenido de la posición
	if (laberinto[fila][columna] == '#') {
		cout << "Error: La posicion ingresada contiene una pared." << endl;
		return false;
	}
	//Verificar la posición inicial
	if (fila == 1 && columna == 1)
	{
		cout << "Usted se encuentra en la coordenada inicial" << endl;
		return false;
	}
	cout << "La coordenada ingresada esta vacia" << endl;
	return true;
}

bool Sistema::encontrarCamino(const Posicion& actual, const Posicion& objetivo, vector<Posicion>& camino)
{
	// Verificar si estamos fuera de los límites de la matriz o si la posición actual es una pared
	if (actual.row < 0 || actual.row >= 10 || actual.col < 0 || actual.col >= 10 || laberinto[actual.row][actual.col] == '#') {
		return false;
	}

	// Verificar si hemos llegado a la posición final
	if (actual.row == objetivo.row && objetivo.col == actual.col) {
		camino.push_back(actual);
		return true;
	}

	// Marcar la posición actual como visitada
	this->laberinto[actual.row][actual.col] = '#';

	// Definir los movimientos posibles (arriba, abajo, izquierda, derecha)
	const int dr[] = { -1, 1, 0, 0 };
	const int dc[] = { 0, 0, -1, 1 };

	// Explorar los movimientos posibles
	for (int i = 0; i < 4; ++i) {
		int newRow = actual.row + dr[i];
		int newCol = actual.col + dc[i];

		// Llamar recursivamente a la función para explorar desde la nueva posición
		if (encontrarCamino(Posicion(newRow, newCol), objetivo, camino)) {
			// Agregar la posición actual a la ruta
			camino.push_back(actual);
			return true;
		}
	}

	// Desmarcar la posición actual
	this->laberinto[actual.row][actual.col] = ' ';

	return false;
}

void Sistema::Menu()
{
	this->laberinto = leerLaberinto();

	/*int fila = 1;
	int columna = 2;

	cout << "Ingrese cordenadas" << endl;
	cin >> fila;
	cin >> columna;

	verificarPosicion(this->laberinto, fila, columna);
	*/

	Posicion inicio(1, 1);  // Posición inicial
	Posicion objetivo(8, 7);   // Posición final

	// Vector para almacenar el camino encontrado
	vector<Posicion> camino;

	// Encontrar el camino
	if (encontrarCamino(inicio, objetivo, camino)) {
		// Imprimir el camino encontrado en orden inverso (desde la posición final hasta la inicial)
		for (auto it = camino.rbegin(); it != camino.rend(); ++it) {
			cout << "(" << it->row << "," << it->col << ") ";
		}
		cout << endl;
	}
	else {
		cout << "No se encontro un camino valido." << endl;
	}

}



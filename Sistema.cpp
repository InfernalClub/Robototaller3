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

		cout << "El archivo fue cargado con exito" << endl;

		archivo.close();
	}
	else
	{
		cout << "No se pudo abrir el archivo." << endl;
		exit(1);
	}
	return laberinto;
}

bool Sistema::verificarPosicion(const vector<vector<char>>& laberinto, int fila, int columna)
{
	// Verificar si los valores ingresados son numeros o caracteres
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
	cout << "La coordenada ingresada esta vacia" << endl;
	return true;
}

void Sistema::encontrarCaminos(const Posicion& actual, const Posicion& objetivo, vector<Posicion>& camino, vector<vector<Posicion>>& caminosEncontrados)
{
	// Verificar si estamos fuera de los límites de la matriz o si la posición actual es una pared
	if (actual.row < 0 || actual.row >= laberinto.size() || actual.col < 0 || actual.col >= laberinto[actual.row].size() || laberinto[actual.row][actual.col] == '#') {
		return;
	}

	// Verificar si hemos llegado a la posición final
	if (actual.row == objetivo.row && actual.col == objetivo.col) {
		caminosEncontrados.push_back(camino);
		return;
	}

	// Marcar la posición actual como visitada
	char temp = laberinto[actual.row][actual.col];
	laberinto[actual.row][actual.col] = '#';

	// Definir los movimientos posibles (arriba, abajo, izquierda, derecha)
	const int dr[] = { -1, 1, 0, 0 };
	const int dc[] = { 0, 0, -1, 1 };

	// Explorar los movimientos posibles
	for (int i = 0; i < 4; ++i) {
		int newRow = actual.row + dr[i];
		int newCol = actual.col + dc[i];

		// Llamar recursivamente a la función para explorar desde la nueva posición
		if (newRow >= 0 && newRow < laberinto.size() && newCol >= 0 && newCol < laberinto[newRow].size() && laberinto[newRow][newCol] != '#') {
			camino.push_back(Posicion(newRow, newCol));
			encontrarCaminos(Posicion(newRow, newCol), objetivo, camino, caminosEncontrados);
			camino.pop_back();
		}
	}

	// Desmarcar la posición actual
	laberinto[actual.row][actual.col] = temp;
}

void Sistema::ejecutarEnHilo(const Posicion& inicio, const Posicion& objetivo, mutex& mutex, int numHilos, vector<vector<Posicion>>& caminosEncontrados)
{
	vector<thread> hilos;

	// Crear los hilos y ejecutar la función en paralelo
	for (int i = 0; i < numHilos; ++i) {
		hilos.push_back(thread([=, &caminosEncontrados]() {
			vector<Posicion> camino;
			encontrarCaminos(inicio, objetivo, camino, caminosEncontrados);
			}));
	}

	// Esperar a que todos los hilos terminen
	for (auto& hilo : hilos) {
		hilo.join();
	}
}

void Sistema::Menu()
{
	cout << "¡Bienvenido a Micromouse!" << endl;
	cout << endl;
	cout << "A continuacion, se realizara la carga" << endl;
	cout << "del archivo laberinto.txt" << endl;
	cout << endl;
	cout << "Cargando..." << endl;
	cout << endl;

	this->laberinto = leerLaberinto();
	mutex mutex;
	vector<thread> hilos;
	vector<vector<Posicion>> caminosEncontrados;

	int filaInicio = 0;
	int columnaInicio = 0;
	int filaFinal = 0;
	int columnaFinal = 0;

	cout << endl << "Ingrese coordenadas iniciales" << endl;
	cin >> filaInicio;
	cin >> columnaInicio;

	while (verificarPosicion(this->laberinto, filaInicio, columnaInicio)) {
		Posicion inicio(filaInicio, columnaInicio); // Posición inicial
		cout << endl << "Ingrese coordenadas finales" << endl;
		cin >> filaFinal;
		cin >> columnaFinal;

		// Verifica si la posición final es la inicial
		while (filaFinal != filaInicio || columnaFinal != columnaInicio) {
			if (verificarPosicion(this->laberinto, filaFinal, columnaFinal)) {
				Posicion objetivo(filaFinal, columnaFinal); // Posición final 

				// Vector para almacenar el camino encontrado
				vector<Posicion> camino;
				// Vector para almacenar los dintintos caminos encontrados
				vector<vector<Posicion>> caminosEncontrados;

				ejecutarEnHilo(inicio, objetivo, mutex, 4, caminosEncontrados);

				if (caminosEncontrados.empty()) {
					cout << endl << "No existen caminos entre la casilla de inicio (" << inicio.row << ", " << inicio.col << ") y la casilla final (" << objetivo.row << ", " << objetivo.col << ")" << endl;
				}
				else {
					cout << endl << "Caminos encontrados de (" << inicio.row << ", " << inicio.col << ") a (" << objetivo.row << ", " << objetivo.col << "):" << endl;
					int ruta = 1;
					for (const auto& camino : caminosEncontrados) {
						cout << "Ruta " << ruta << ":" << endl;
						cout << "(" << inicio.row << ", " << inicio.col << ") -> Coordenada inicial" << endl;
						for (size_t i = 0; i < camino.size() - 1; ++i) {
							cout << "(" << camino[i].row << ", " << camino[i].col << ")" << endl;
						}
						cout << "(" << camino.back().row << ", " << camino.back().col << ") -> Coordenada final" << endl;
						cout << endl;
						ruta++;
					}
				}

				// Limpiar los caminos encontrados para la siguiente búsqueda
				caminosEncontrados.clear();
				return;
			}
			else {
				cout << endl << "Coordenadas invalidas. Ingrese nuevamente las coordenadas finales." << endl;
			}

			cout << endl << "Ingrese coordenadas finales" << endl;
			cin >> filaFinal;
			cin >> columnaFinal;
		}
		cout << endl << "Ingrese coordenadas iniciales" << endl;
		cin >> filaInicio;
		cin >> columnaInicio;
	}
}

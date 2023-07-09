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

	bool coordenadasValidas = false;

	while (!coordenadasValidas)
	{
		// Ingreso y verificación de la coordenada inicial
		while (true)
		{
			cout << "Ingrese el primer valor de la coordenada inicial" << endl;
			if (cin >> filaInicio)
			{
				cout << "Ingrese el segundo valor de la coordenada inicial" << endl;
				if (cin >> columnaInicio)
				{
					// Verificar la posición inicial
					if (verificarPosicion(this->laberinto, filaInicio, columnaInicio))
					{
						break;  // Salir del bucle si las coordenadas son válidas
					}
					else
					{
						cout << "Coordenadas iniciales no validas. Por favor ingrese nuevamente." << endl;
					}
				}
				else
				{
					cout << "Valor no valido. Por favor ingrese nuevamente." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}
			else
			{
				cout << "Valor no valido. Por favor ingrese nuevamente." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}

		// Ingreso y verificación de la coordenada final
		while (true)
		{
			cout << "Ingrese el primer valor de la coordenada final" << endl;
			if (cin >> filaFinal)
			{
				cout << "Ingrese el segundo valor de la coordenada final" << endl;
				if (cin >> columnaFinal)
				{
					// Verificar la posición final
					if (verificarPosicion(this->laberinto, filaFinal, columnaFinal))
					{
						if (filaFinal != filaInicio || columnaFinal != columnaInicio)
						{
							coordenadasValidas = true;  // Establecer coordenadas válidas y salir del bucle
							break;
						}
						else
						{
							cout << "Coordenadas finales no pueden ser iguales a las coordenadas iniciales. Por favor ingrese nuevamente." << endl;
						}
					}
					else
					{
						cout << "Coordenadas finales no validas. Por favor ingrese nuevamente." << endl;
					}
				}
				else
				{
					cout << "Valor no valido. Por favor ingrese nuevamente." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}
			else
			{
				cout << "Valor no valido. Por favor ingrese nuevamente." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}

		if (!coordenadasValidas)
		{
			cout << "Las coordenadas iniciales y finales son iguales. Por favor, ingrese nuevas coordenadas." << endl;
		}
	}

	Posicion inicio(filaInicio, columnaInicio); // Posición inicial
	Posicion objetivo(filaFinal, columnaFinal); // Posición final 

	// Vector para almacenar el camino encontrado
	vector<Posicion> camino;

	// Ejecutar búsqueda de caminos
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
}


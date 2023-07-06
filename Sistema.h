#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <mutex>
#include <cctype>

using namespace std;
class Sistema
{
private:
	vector<vector<char>> laberinto;

public: 
	vector <vector<char>> leerLaberinto();
	bool verificarPosicion(const vector<vector<char>>& laberinto, int fila, int columna);

	struct Posicion
	{
		int row;
		int col;
		Posicion(int r, int c) : row(r), col(c) {}
	};

	void encontrarCaminos(const Posicion& actual, const Posicion& objetivo, vector<Posicion>& camino, vector<vector<Posicion>>& caminosEncontrados);
	void ejecutarEnHilo(const Posicion& inicio, const Posicion& objetivo, mutex& mutex, int numHilos, vector<vector<Posicion>>& caminosEncontrados);
	void Menu();
};


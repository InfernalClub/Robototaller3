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

	bool encontrarCamino(const Posicion& actual, const Posicion& objetivo, vector<Posicion>& camino);
	void Menu();
};


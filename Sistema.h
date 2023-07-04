#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <mutex>
#include <cctype>
#include "Nodo.h"

using namespace std;
class Sistema
{
private:
	Nodo* nodo;
	int fila = 1;
	int columna = 1;
	vector<vector<char>> laberinto;

public: 
	void lecturaArchivo();
    void Menu();
	void comprobarPosicion(int fila, int columna);
};


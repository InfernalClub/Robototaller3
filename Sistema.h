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
	int fila = 0;
	int columna = 0;
	char valor1 = '\0';
	char valor2 = '\0';
	vector<vector<char>> laberinto;

public: 
	void lecturaArchivo();
    void Menu();
	void comprobarPosicion(int fila, int columna);
};


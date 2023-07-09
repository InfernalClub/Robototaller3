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
	//Matriz dedicada a almacenar el "laberinto.txt"
	vector<vector<char>> laberinto;

public: 
	//Lectura del laberinto.txt"
	vector <vector<char>> leerLaberinto();
	/*Valida si la la posicion enviada por el usuario cumple con los requisito de que no sea una pared o que este dentro de los limites
	de la matriz correspondiente*/
	bool verificarPosicion(const vector<vector<char>>& laberinto, int fila, int columna);
	//Estructura basica con la cual se crean las coordenadas de posicion para el usuario
	struct Posicion
	{
		int row;
		int col;
		Posicion(int r, int c) : row(r), col(c) {}
	};
	//Funcion dedicada a buscar todos los caminos posibles dentro del laberinto
	void encontrarCaminos(const Posicion& actual, const Posicion& objetivo, vector<Posicion>& camino, vector<vector<Posicion>>& caminosEncontrados);
	//Funcion dedicada a implementar el uso de los hilos para la creacion de las rutas
	void ejecutarEnHilo(const Posicion& inicio, const Posicion& objetivo, mutex& mutex, int numHilos, vector<vector<Posicion>>& caminosEncontrados);
	//Menu principal en donde el usuario interactua con todo el programa
	void Menu();
};


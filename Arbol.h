#pragma once
#include "Nodo.h"
#include <queue>
#include <iostream>

using namespace std;
class Arbol
{
private:
	Nodo* root;
public:
	Arbol();
	~Arbol() = default;
	void insertarArbol(Nodo* root, Robot* robot);
	void mostrarArbol(Nodo* root);
};


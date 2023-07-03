#pragma once
#include "Robot.h"
class Nodo
{
private:
	Robot* robot;
	Nodo* arriba;
	Nodo* abajo;
	Nodo* izq;
	Nodo* der;
public:
	Nodo(Robot* robot);
	~Nodo() = default;
};


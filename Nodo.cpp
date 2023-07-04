#include "Nodo.h"

Nodo::Nodo(char letra)
{
	this->letra = letra;
	this->izq = nullptr;
	this->der = nullptr;
}

Nodo::~Nodo()
{
	delete[] this->izq;
	delete[] this->der;
}

char Nodo::getLetra()
{
	return this->letra;
}

Nodo* Nodo::getIzq()
{
	return this->izq;
}

Nodo* Nodo::getDer()
{
	return this->der;
}

void Nodo::setLetra(char letra)
{
	this->letra = letra;
}

void Nodo::setIzq(Nodo* izq)
{
	this->izq = izq;
}

void Nodo::setDer(Nodo* der)
{
	this->der = der;
}
#pragma once
class Nodo
{
private:
	char letra;
	Nodo* izq;
	Nodo* der;

public:
	Nodo(char letra);
	~Nodo();

	char getLetra();
	Nodo* getIzq();
	Nodo* getDer();

	void setLetra(char letra);
	void setIzq(Nodo* izq);
	void setDer(Nodo* der);
};


#include "Arbol.h"

Arbol::Arbol()
{
	this->root = nullptr;
}

void Arbol::insertarArbol(Nodo* root, Robot* robot)
{
	if (root == nullptr) {
		Nodo* root = new Nodo(robot);
		return;
	}
}

void Arbol::mostrarArbol(Nodo* root)
{
	if (root == nullptr) {
		return;
	}

	queue<Nodo*> q;
	q.push(root);

	while (!q.empty()) {
		Nodo* actual = q.front();
		q.pop();

		cout << actual->getRobot()->getCaracter() << " ";

		if (actual->getHijoIzq() != nullptr)
			q.push(actual->getHijoIzq());

		if (actual->getHijoDer() != nullptr)
			q.push(actual->getHijoDer());
	}
}

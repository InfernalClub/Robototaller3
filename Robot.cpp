#include "Robot.h"

Robot::Robot(char caracter, int posicionX, int posicionY)
{
	this->caracter = caracter;
	this->posicionX = posicionX;
	this->posicionY = posicionY;
}

Robot::~Robot()
{
}

char Robot::getCaracter()
{
	return this->caracter;
}

int Robot::getPosicionX()
{
	return this->posicionX;
}

int Robot::getPosicionY()
{
	return this->posicionY;
}

void Robot::setCaracter(char caracter)
{
	this->caracter = caracter;
}

void Robot::setPosicionX(int posicionX)
{
	this->posicionX = posicionX;
}

void Robot::setPosicionY(int posicionY)
{
	this->posicionY = posicionY;
}

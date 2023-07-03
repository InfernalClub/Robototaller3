#pragma once
class Robot
{
private: 
	char caracter = '\0';
	int posicionX = 0;
	int posicionY = 0;

public:
	Robot(char caracter, int posicionX, int posicionY);
	~Robot();
	char getCaracter();
	int getPosicionX();
	int getPosicionY();
	void setCaracter(char caracter);
	void setPosicionX(int posicionX);
	void setPosicionY(int posicionY);
};


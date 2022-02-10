#ifndef _COLISION_H_
#define _COLISION_H_

#include "cameraclass.h"

/*
	COLISION EXTERNA
		el jugador se encuentra fuera del radio de la colision y esta limita su avance evitando que entre a cierta area
	COLISION INTERNA
		el jugador se mueve dentro del radio de la colision y esta le impide salir de cierta area
*/

//variable globales
extern float storedPos[2];

class Colision
{
private:
	const char* tipo; // 'i' para interno y 'e' para externo
	float Radio;
	float Centro[2];
	float storedPos[2]; //posicion guardada
public:
	bool ColisionRadar(CameraClass*, Colision*); //calculo para validacion //Aqui se llenan las coordenadas del centro y del radio, se establece el tipo
	void StorePosicion(CameraClass*, bool);
	void UpdateColision(float, float, float);
	bool HeightColisionRadar(float);
	Colision* ColisionPointerSend();
	Colision(float, float, float, const char*);
	~Colision();

};

#endif
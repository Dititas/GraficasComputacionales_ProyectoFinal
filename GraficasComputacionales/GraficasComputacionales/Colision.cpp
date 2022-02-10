#include "Colision.h"
#include "Colision.h"

bool Colision::ColisionRadar(CameraClass* playerCamera, Colision* playerColision)
{
	float DistaciaEntreCentros = sqrtf(((powf((Centro[0] - playerCamera->GetXPos()), 2)) + (powf((Centro[1] - playerCamera->GetZPos()), 2))));
	if (tipo == "e")  //externa
	{
		//si la distancia entre los centros es menor a la suma de los radios hay colision
		if (DistaciaEntreCentros <= (this->Radio + playerColision->Radio))
		{
			return true;
		}
		//si la distancia entre los centros es mayor a la suma de los radios no hay colision
		if (DistaciaEntreCentros > (this->Radio + playerColision->Radio))
		{
			return false;
		}
	}
	if (tipo == "i") //interna
	{
		//si la distancia entre el jugador es mayor al radio fijado hay colision
		if (DistaciaEntreCentros > this->Radio)
		{
			return true;
		}
		if (DistaciaEntreCentros < this->Radio)
		{
			return false;
		}
	}
}

void Colision::StorePosicion(CameraClass* playerCamera, bool estatus)
{
	if (estatus == true)
	{
		float tmpY = playerCamera->GetYPos();
		playerCamera->SetPosition(storedPos[0], tmpY, storedPos[1]);
		estatus = false;
		return;
	}
	if (estatus == false)
	{
		storedPos[0] = playerCamera->GetXPos();
		storedPos[1] = playerCamera->GetZPos();
		return;
	}
}

void Colision::UpdateColision(float new_X, float new_Z, float new_Radio)
{
	this->Centro[0] = new_X;
	this->Centro[1] = new_Z;
	if (new_Radio <= 0)
	{
		return;
	}
	if (new_Radio > 0)
	{
		this->Radio = new_Radio;
		return;
	}
}

bool Colision::HeightColisionRadar(float alturaTerreno)
{
	if (alturaTerreno >= 12)
	{
		return true;
	}
	else if (alturaTerreno < 12)
	{
		return false;
	}

}

Colision* Colision::ColisionPointerSend()
{
	return this;
}

Colision::Colision(float centro_x, float centro_z, float radio_r, const char* tipo_t)
{
	this->Centro[0] = centro_x;
	this->Centro[1] = centro_z;
	this->Radio = radio_r;
	this->tipo = tipo_t;
	storedPos[0] = -12;
	storedPos[1] = -137;

}

Colision::~Colision()
{

}
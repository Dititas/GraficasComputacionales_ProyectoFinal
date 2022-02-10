////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "openglclass.h"
#include "cameraclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "Terreno.h"
#include "SkyDome.h"
#include "Billboard.h"
#include "Modelos.h"
#include "Colision.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;




////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();
	bool UnaVez;
	bool tercera;
	bool Initialize(OpenGLClass*, HWND);
	void Shutdown();
	bool Frame();
	float angx, angy, angz, height, vel;
	float XposF, YposF, ZposF;
	float palmXZ[20][2];
	float pastoXZ[20][2];
	void posicionCamara();


private:
	bool Render(float);

private:
	//Billboards
	Billboard* palmera;
	Billboard* pasto;
	Billboard* rocastnd;


	//Modelos
	Modelos* foca;
	Modelos* tumba;
	Modelos* FormRoc;
	Modelos* bote;
	Modelos* roca;
	Modelos* casaP1;
	Modelos* casaP2;
	Modelos* casaP3;
	Modelos* casaP4;
	Modelos* casaP5;
	Modelos* mar;
	Modelos* VisualColision;

	//Colsiones
	Colision* colision_Player;
	Colision* colision_Mapa;
	Colision* colision_Islas;
	Colision* colision_Muelle;
	Colision* colision_FormRoc;

	//
	OpenGLClass* m_OpenGL;
	CameraClass* m_Camera;
	Terreno* terreno;
	SkyDome* sky;
	LightShaderClass* m_LightShader;
	LightShaderClass* m_LightShaderSky;
	LightShaderClass* m_BillShader;
	LightShaderClass* m_VeggieShader;
	LightShaderClass* m_ModeloShader;
	LightShaderClass* m_AguaShader;
	LightClass* m_Light;
	float angulo; //El ángulo al que quiero rotar el modelo
	float anguloDeseado; //Este tomará el valor en radianes de lo que necesito
	float convertirGradosRadianes(float angulo) {
		float radianes;
		radianes = angulo * (3.141592 / 180);
		return radianes;
	}
};

#endif
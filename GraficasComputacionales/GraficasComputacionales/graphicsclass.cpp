////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_OpenGL = 0;
	m_Camera = 0;
	m_LightShader = 0;
	m_LightShaderSky = 0;
	m_BillShader = 0;
	m_Light = 0;
	angx = angy = angz = height = 0;
	palmXZ[0][0] = -178;
	palmXZ[0][1] = -107;
	palmXZ[1][0] = -139;
	palmXZ[1][1] = -46;
	palmXZ[2][0] = -68;
	palmXZ[2][1] = -167;
	palmXZ[3][0] = -52;
	palmXZ[3][1] = -139;
	palmXZ[4][0] = 105;
	palmXZ[4][1] = -236;
	palmXZ[5][0] = 171;
	palmXZ[5][1] = -208;
	palmXZ[6][0] = 179;
	palmXZ[6][1] = -241;
	palmXZ[7][0] = 152;
	palmXZ[7][1] = -289;
	palmXZ[8][0] = 169;
	palmXZ[8][1] = 6;
	palmXZ[9][0] = 184;
	palmXZ[9][1] = 60;
	palmXZ[10][0] = 213;
	palmXZ[10][1] = 99;
	palmXZ[11][0] = -163;
	palmXZ[11][1] = 141;
	palmXZ[12][0] = -188;
	palmXZ[12][1] = 154;
	palmXZ[13][0] = -210;
	palmXZ[13][1] = 166;
	palmXZ[14][0] = -129;
	palmXZ[14][1] = 173;
	palmXZ[15][0] = -82;
	palmXZ[15][1] = 141;
	palmXZ[16][0] = 283;
	palmXZ[16][1] = -14;
	palmXZ[17][0] = 289;
	palmXZ[17][1] = 52;
	palmXZ[18][0] = 224;
	palmXZ[18][1] = -17;
	palmXZ[19][0] = 249;
	palmXZ[19][1] = -230;

	pastoXZ[0][0] = -136;
	pastoXZ[0][1] = 182;
	pastoXZ[1][0] = -145;
	pastoXZ[1][1] = 178;
	pastoXZ[2][0] = -157;
	pastoXZ[2][1] = 172;
	pastoXZ[3][0] = -163;
	pastoXZ[3][1] = 151;
	pastoXZ[4][0] = -140;
	pastoXZ[4][1] = 167;
	pastoXZ[5][0] = -130;
	pastoXZ[5][1] = 165;
	pastoXZ[6][0] = 241;
	pastoXZ[6][1] = 64;
	pastoXZ[7][0] = 214;
	pastoXZ[7][1] = 57;
	pastoXZ[8][0] = 211;
	pastoXZ[8][1] = 48;
	pastoXZ[9][0] = 206;
	pastoXZ[9][1] = 39;
	pastoXZ[10][0] = 194;
	pastoXZ[10][1] = 36;
	pastoXZ[11][0] = 174;
	pastoXZ[11][1] = -230;
	pastoXZ[12][0] = 150;
	pastoXZ[12][1] = -252;
	pastoXZ[13][0] = 185;
	pastoXZ[13][1] = -236;
	pastoXZ[14][0] = 165;
	pastoXZ[14][1] = -254;
	pastoXZ[15][0] = -65;
	pastoXZ[15][1] = -144;
	pastoXZ[16][0] = -58;
	pastoXZ[16][1] = -137;
	pastoXZ[17][0] = -53;
	pastoXZ[17][1] = -126;
	pastoXZ[18][0] = -58;
	pastoXZ[18][1] = -93;
	pastoXZ[19][0] = -70;
	pastoXZ[19][1] = -81;

	bool tercera = false;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(OpenGLClass* OpenGL, HWND hwnd)
{
	bool result;



	// Store a pointer to the OpenGL class object.
	m_OpenGL = OpenGL;

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}



	terreno = new Terreno(hwnd, m_OpenGL, L"Heightmap.jpg", L"Grass_Diffuse.jpg", L"Grass_Normal.jpg", L"Concrete_Diffuse.jpg", L"Concrete_Normal.jpg", L"Channel_R.png",
		(float)1000, (float)1000, 0, 1, 3, 4, 24, 25);

	// Create the light shader object.
	m_LightShader = new LightShaderClass((char*)"light.vs", (char*)"light.ps");
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_OpenGL, hwnd);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetDiffuseColor(1.0f, 0.85f, 0.66f, 1.0f);
	m_Light->SetDirection(-1.0f, 1.5f, -1.0f);

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, terreno->Superficie(m_Camera->GetXPos(), m_Camera->GetZPos()) + 6, 430.0f);


	//sky = new SkyDome(hwnd, m_OpenGL, 32, 32, 400, L"sky.jpg");
	//// Create the light shader object.
	//m_LightShaderSky = new LightShaderClass((char*)"Sky.vs", (char*)"Sky.ps");
	//if (!m_LightShaderSky)
	//{
	//	return false;
	//}

	// Initialize the light shader object.
	//result = m_LightShaderSky->Initialize(m_OpenGL, hwnd);
	//if (!result)
	//{
	//	MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
	//	return false;
	//}


	// Create the light shader object.
	//m_BillShader = new LightShaderClass((char*)"Sky.vs", (char*)"Sky.ps");
	//if (!m_BillShader)
	//{
	//	return false;
	//}

	//// Initialize the light shader object.
	//result = m_BillShader->Initialize(m_OpenGL, hwnd);
	//if (!result)
	//{
	//	MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
	//	return false;
	//}

	/*m_VeggieShader = new LightShaderClass((char*)"Bill.vs", (char*)"Bill.ps");
	if (!m_VeggieShader)
	{
		return false;
	}

	result = m_VeggieShader->Initialize(m_OpenGL, hwnd);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}*/

	float ancho = 0;


#pragma region Billboards

	//palmera = new Billboard(hwnd, m_OpenGL, L"palmera2.png", L"palmera2Norm.png", 50, 51, 50.0f, 100.f, 100.0f, -70, -70);
	//pasto = new Billboard(hwnd, m_OpenGL, L"IntentoDePasto.png", L"IntentoDePasto_Normal.png", 39, 40, 30.0f, 30.f, 30.0f, 0, 0);
	//rocastnd = new Billboard(hwnd, m_OpenGL, L"RocaStnd.png", L"RocaStnd_Normal.png", 41, 42, 20.0f, 20.0f, 20.0f, 0, 0);

#pragma endregion

#pragma region CreacionDeColisiones
	/////////////////////////////new Colision(centroX,centroZ, radio, tipo) excepto islas////////////////////////////////////////
	/*colision_Player = new Colision(0, 0, 5, "e");
	colision_Mapa = new Colision(0, 0, 395, "i");
	colision_Islas = new Colision(0, 0, 1, "i");
	colision_Muelle = new Colision(-23, -117, 5, "e");
	colision_FormRoc = new Colision(0, 325, 200, "e");*/
#pragma enregion

#pragma region Carga de Modelos

	//esfingeTest = new Modelos(hwnd, m_OpenGL, "es5.obj", L"esfingeBase.jpg", L"esfingeNorm4.jpg", L"esfingeSpecular.png" , 4.0, 250.0, 54.0, 0.0, 2);
	//VisualColision = new Modelos(hwnd, m_OpenGL, "Visualcolision.obj", L"default_color.jpg", L"tiles_normal.jpg", L"FormRoc_specular.jpg,", 200, 0.0, 15.0, 300.0, 2);
	//foca = new Modelos(hwnd, m_OpenGL, "foca.obj", L"foca_color.jpg", L"foca_normal.jpg", L"foca_specular.jpg,", 0.5, 222.0, 28.0, 73.0, 2);
	//FormRoc = new Modelos(hwnd, m_OpenGL, "FormRoc.obj", L"FormRoc_color.jpg", L"FormRoc_normal.jpg", L"FormRoc_specular.jpg,", 1.0, 61.0, -19.0, 263.0, 3);
	//bote = new Modelos(hwnd, m_OpenGL, "Bote.obj", L"Bote_color.jpg", L"Bote_normal.jpg", L"Bote_specular.jpg,", 0.02, 0.0, 0.0, 0.0, 4);
	//tumba = new Modelos(hwnd, m_OpenGL, "TumbaM.obj", L"Tumba_color.jpg", L"Tumba_normal.jpg", L"Tumba_specular.jpg,", 0.4, -186.0, 20.0, 200.0, 5);
	//casaP1 = new Modelos(hwnd, m_OpenGL, "Base01.obj", L"baseC_color01.jpg", L"baseC_normal01.jpg", L"baseC_specular01.jpg,", 0.15, -64.0, 12.7, -113.0, 6);
	//casaP2 = new Modelos(hwnd, m_OpenGL, "Base02.obj", L"baseC_color01.jpg", L"baseC_normal01.jpg", L"baseC_specular01.jpg,", 0.15, -64.0, 12.7, -113.0, 7);
	//casaP3 = new Modelos(hwnd, m_OpenGL, "Base03.obj", L"baseC_color02.jpg", L"baseC_normal02.jpg", L"baseC_specular02.jpg,", 0.15, -64.0, 12.7, -113.0, 9);
	//casaP4 = new Modelos(hwnd, m_OpenGL, "Base04.obj", L"baseC_color03.jpg", L"baseC_normal03.jpg", L"baseC_specular03.jpg,", 0.15, -64.0, 12.7, -113.0, 10);
	//casaP5 = new Modelos(hwnd, m_OpenGL, "Base05.obj", L"baseC_color01.jpg", L"baseC_normal01.jpg", L"baseC_specular01.jpg,", 0.15, -64.0, 12.7, -113.0, 11);
	mar = new Modelos(hwnd, m_OpenGL, "Mar.obj", L"water_color.jpg", L"water_normalB.png", L"water_specular.png,", 0.4f, -12.0f, 95.0f, -137.0f, 12.0f);

	//m_ModeloShader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
	m_AguaShader = new LightShaderClass((char*)"Agua.vs", (char*)"Agua.ps");

	//if (!m_ModeloShader)
	//{
	//	return false;
	//}
	if (!m_AguaShader)
	{
		return false;
	}

#pragma endregion
	// Initialize the light shader object.
	/*result = m_ModeloShader->Initialize(m_OpenGL, hwnd);
	if (!result)
	{

		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}*/

	result = m_AguaShader->Initialize(m_OpenGL, hwnd);
	if (!result)
	{

		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown(m_OpenGL);
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the light shader object.
	if (m_LightShaderSky)
	{
		m_LightShaderSky->Shutdown(m_OpenGL);
		delete m_LightShaderSky;
		m_LightShaderSky = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the terreno object.
	if (terreno)
	{
		delete terreno;
		m_Camera = 0;
	}


	// Release the pointer to the OpenGL class object.
	m_OpenGL = 0;

	return;
}


bool GraphicsClass::Frame()
{
	bool result;
	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += 0.0174532925f * 2.0f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	return true;
}

void GraphicsClass::posicionCamara()
{
	XposF = m_Camera->GetXPos();
	YposF = m_Camera->GetYPos();
	ZposF = m_Camera->GetZPos();
}



bool GraphicsClass::Render(float rotation)
{
	float worldMatrix[16];
	float viewMatrix[16];
	float projectionMatrix[16];
	float lightDirection[3];
	float diffuseLightColor[4];
	float worldMatrixBill[16];

	float factAtAmb = 0.6f;
	float factAtDif = 1.0f;
	float factAtSpec = 1.0f;

	// Clear the buffers to begin the scene.
	m_OpenGL->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->SetRotation(angx, angy, angz);
	m_Camera->SetYPos(terreno->Superficie(m_Camera->GetXPos(), m_Camera->GetZPos()) + 6);

	if (tercera)
	{
		/*m_Camera->SetYPos(15.5);*/
	}
	else
	{
		/*m_Camera->SetYPos(15);*/
	}


	/*colision_Mapa->StorePosicion(m_Camera->CameraPointerSend(), colision_Mapa->ColisionRadar(m_Camera->CameraPointerSend(), colision_Player->ColisionPointerSend()));
	colision_Islas->StorePosicion(m_Camera->CameraPointerSend(), colision_Islas->HeightColisionRadar(terreno->Superficie(m_Camera->GetXPos(), m_Camera->GetZPos())));
	colision_Muelle->StorePosicion(m_Camera->CameraPointerSend(), colision_Muelle->ColisionRadar(m_Camera->CameraPointerSend(), colision_Player->ColisionPointerSend()));
	colision_FormRoc->StorePosicion(m_Camera->CameraPointerSend(), colision_FormRoc->ColisionRadar(m_Camera->CameraPointerSend(), colision_Player->ColisionPointerSend()));*/
	//if (tercera)
	//{
	//	colision_Player->UpdateColision(m_Camera->GetXPos() + m_Camera->GetLookX() * 4, m_Camera->GetZPos() + m_Camera->GetLookZ() * 4, 0);
	//}
	//else
	//{
	//	colision_Player->UpdateColision(m_Camera->GetXPos(), m_Camera->GetZPos(), 0);
	//}

	m_Camera->Render(vel);

	// Get the world, view, and projection matrices from the opengl and camera objects.
	m_OpenGL->GetWorldMatrix(worldMatrix);
	m_OpenGL->GetWorldMatrix(worldMatrixBill);
	m_Camera->GetViewMatrix(viewMatrix);
	m_OpenGL->GetProjectionMatrix(projectionMatrix);

	// Get the light properties.
	m_Light->GetDirection(lightDirection);
	m_Light->GetDiffuseColor(diffuseLightColor);

	glDisable(GL_DEPTH_TEST);
	/*m_LightShaderSky->SetShader(m_OpenGL);
	m_LightShaderSky->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrix);
	m_LightShaderSky->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_LightShaderSky->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_LightShaderSky->Pon1Entero(m_OpenGL, (char*)"cielo", 2);
	m_LightShaderSky->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	m_LightShaderSky->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	sky->Render(m_OpenGL);*/
	glEnable(GL_DEPTH_TEST);
	// Rotate the world matrix by the rotation value so that the triangle will spin.
	//m_OpenGL->MatrixRotationY(worldMatrix, rotation);

	// Set the light shader as the current shader program and set the matrices that it will use for rendering.
#pragma region Terreno
	m_LightShader->SetShader(m_OpenGL);
	m_LightShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrix);
	m_LightShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_LightShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_LightShader->Pon1Entero(m_OpenGL, (char*)"shaderTexture", 0);		//sand
	m_LightShader->Pon1Entero(m_OpenGL, (char*)"shaderTexture2", 1);	//sandNrm
	m_LightShader->Pon1Entero(m_OpenGL, (char*)"shaderTexture3", 3);	//Dirt
	m_LightShader->Pon1Entero(m_OpenGL, (char*)"shaderTexture4", 4);	//grass
	m_LightShader->Pon1Entero(m_OpenGL, (char*)"shaderTexture5", 25);	//blend
	m_LightShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	m_LightShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	// Render the model using the light shader.
	terreno->Render(m_OpenGL);
#pragma endregion

	//#pragma visualColisionTest
	//
	//	m_ModeloShader->SetShader(m_OpenGL);
	//	float modmatrix[16];
	//	float rotacionYmod[16];
	//	float rotacionY_R[16]{};
	//	m_OpenGL->GetWorldMatrix(modmatrix);
	//	m_OpenGL->MatrixTranslation(modmatrix, VisualColision->x, VisualColision->y, VisualColision->z);
	//	m_OpenGL->MatrixRotationY(rotacionYmod, 0.0);
	//	m_OpenGL->MatrixMultiply(rotacionY_R, rotacionYmod, modmatrix);
	//	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", rotacionY_R);
	//	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	//	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	//	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"colorText", 6);
	//	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"normText", 7);
	//	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"specText", 8);
	//	m_ModeloShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	//	float campos[3] = { m_Camera->GetXPos(), m_Camera->GetYPos(), m_Camera->GetZPos() };
	//	m_ModeloShader->PonVec3(m_OpenGL, (char*)"camaraDir", campos);
	//	//enviar ka, kd y ks al shader
	//	m_ModeloShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	//
	//	VisualColision->Render(m_OpenGL);
	//	
	//
	//#pragma endregion

#pragma region foca
	//m_ModeloShader->SetShader(m_OpenGL);
	//float modmatrix[16];
	//float rotacionYmod[16];
	//float rotacionY_R[16]{};
	//m_OpenGL->GetWorldMatrix(modmatrix);
	//m_OpenGL->MatrixTranslation(modmatrix, foca->x, foca->y, foca->z);
	//m_OpenGL->MatrixRotationY(rotacionYmod, this->convertirGradosRadianes(272));
	//m_OpenGL->MatrixMultiply(rotacionY_R, rotacionYmod, modmatrix);
	//m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", rotacionY_R);
	//m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	//m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	//m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"colorText", 6);
	//m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"normText", 7);
	//m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"specText", 8);
	//m_ModeloShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	//float campos[3] = { m_Camera->GetXPos(), m_Camera->GetYPos(), m_Camera->GetZPos() };
	//m_ModeloShader->PonVec3(m_OpenGL, (char*)"camaraDir", campos);
	////enviar ka, kd y ks al shader
	//m_ModeloShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);

	//foca->Render(m_OpenGL);

#pragma endregion

#pragma region FormRoc
	//m_ModeloShader->SetShader(m_OpenGL);
	//float modmatrix_2[16];
	//float rotacionYmod_2[16];
	//m_OpenGL->GetWorldMatrix(modmatrix_2);
	//m_OpenGL->MatrixTranslation(modmatrix_2, FormRoc->x, FormRoc->y, FormRoc->z);
	//m_OpenGL->MatrixRotationY(rotacionYmod_2, 0.0);
	//m_OpenGL->MatrixMultiply(modmatrix_2, rotacionYmod_2, modmatrix_2);
	//m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix_2);
	//m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	//m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	//m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"colorText", 9);
	//m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"normText", 10);
	//m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"specText", 11);
	//m_ModeloShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	//float campos_2[3] = { m_Camera->GetXPos(), m_Camera->GetYPos(), m_Camera->GetZPos() };
	//m_ModeloShader->PonVec3(m_OpenGL, (char*)"camaraDir", campos_2);
	////enviar ka, kd y ks al shader
	//m_ModeloShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);

	//FormRoc->Render(m_OpenGL);

#pragma endregion

#pragma region bote
	//float boteX = 0;
	//float boteY = 0;
	//float boteZ = 0;
	//if (tercera)
	//{

	//	boteX = m_Camera->GetXPos() + m_Camera->GetLookX() * 4;
	//	boteY = 14;
	//	boteZ = m_Camera->GetZPos() + m_Camera->GetLookZ() * 4;
	//}
	//else
	//{
	//	boteX = m_Camera->GetXPos();
	//	boteY = 14;
	//	boteZ = m_Camera->GetZPos();
	//}


	//m_ModeloShader->SetShader(m_OpenGL);
	//float modmatrix_3[16];
	//float rotacionYmod_3[16];
	//float rotacionModR[16]{};
	//m_OpenGL->GetWorldMatrix(modmatrix_3);
	//m_OpenGL->MatrixTranslation(modmatrix_3, boteX, boteY, boteZ);
	//m_OpenGL->MatrixRotationY(rotacionYmod_3, this->convertirGradosRadianes((angy - 90)));
	//m_OpenGL->MatrixMultiply(rotacionModR, rotacionYmod_3, modmatrix_3);
	//m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", rotacionModR);
	//m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	//m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	//m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"colorText", 12);
	//m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"normText", 13);
	//m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"specText", 14);
	//m_ModeloShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	//float campos_3[3] = { m_Camera->GetXPos(), m_Camera->GetYPos(), m_Camera->GetZPos() };
	//m_ModeloShader->PonVec3(m_OpenGL, (char*)"camaraDir", campos_3);
	////enviar ka, kd y ks al shader
	//m_ModeloShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);

	//bote->Render(m_OpenGL);

#pragma endregion

#pragma region tumba
	//m_ModeloShader->SetShader(m_OpenGL);
	//float modmatrix_4[16];
	//float rotacionYmod_4[16];
	//float rotacionYmod_4_R[16]{};
	//m_OpenGL->GetWorldMatrix(modmatrix_4);
	//m_OpenGL->MatrixTranslation(modmatrix_4, tumba->x, tumba->y, tumba->z);
	//m_OpenGL->MatrixRotationY(rotacionYmod_4, this->convertirGradosRadianes(24));
	//m_OpenGL->MatrixMultiply(rotacionYmod_4_R, rotacionYmod_4, modmatrix_4);
	//m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", rotacionYmod_4_R);
	//m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	//m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	//m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"colorText", 15);
	//m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"normText", 16);
	//m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"specText", 17);
	//m_ModeloShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	//float campos_4[3] = { m_Camera->GetXPos(), m_Camera->GetYPos(), m_Camera->GetZPos() };
	//m_ModeloShader->PonVec3(m_OpenGL, (char*)"camaraDir", campos_4);
	////enviar ka, kd y ks al shader
	//m_ModeloShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);

	//tumba->Render(m_OpenGL);

#pragma endregion

#pragma region CasaParte1

	/*m_ModeloShader->SetShader(m_OpenGL);
	float modmatrix_5[16];
	float rotacionYmod_5[16];
	m_OpenGL->GetWorldMatrix(modmatrix_5);
	m_OpenGL->MatrixTranslation(modmatrix_5, casaP1->x, casaP1->y, casaP1->z);
	m_OpenGL->MatrixRotationY(rotacionYmod_5, 0.0);
	m_OpenGL->MatrixMultiply(modmatrix_5, rotacionYmod_5, modmatrix_5);
	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix_5);
	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"colorText", 18);
	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"normText", 19);
	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"specText", 20);
	m_ModeloShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	float campos_5[3] = { m_Camera->GetXPos(), m_Camera->GetYPos(), m_Camera->GetZPos() };
	m_ModeloShader->PonVec3(m_OpenGL, (char*)"camaraDir", campos_5);
	m_ModeloShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	casaP1->Render(m_OpenGL);*/

#pragma endregion

#pragma region CasaParte2

	/*m_ModeloShader->SetShader(m_OpenGL);
	float modmatrix_6[16];
	float rotacionYmod_6[16];
	m_OpenGL->GetWorldMatrix(modmatrix_6);
	m_OpenGL->MatrixTranslation(modmatrix_6, casaP2->x, casaP2->y, casaP2->z);
	m_OpenGL->MatrixRotationY(rotacionYmod_6, 0.0);
	m_OpenGL->MatrixMultiply(modmatrix_6, rotacionYmod_6, modmatrix_6);
	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix_6);
	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"colorText", 21);
	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"normText", 22);
	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"specText", 23);
	m_ModeloShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	float campos_6[3] = { m_Camera->GetXPos(), m_Camera->GetYPos(), m_Camera->GetZPos() };
	m_ModeloShader->PonVec3(m_OpenGL, (char*)"camaraDir", campos_6);
	m_ModeloShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	casaP2->Render(m_OpenGL);*/

#pragma endregion

#pragma region CasaParte3

	/*m_ModeloShader->SetShader(m_OpenGL);
	float modmatrix_7[16];
	float rotacionYmod_7[16];
	m_OpenGL->GetWorldMatrix(modmatrix_7);
	m_OpenGL->MatrixTranslation(modmatrix_7, casaP3->x, casaP3->y, casaP3->z);
	m_OpenGL->MatrixRotationY(rotacionYmod_7, 0.0);
	m_OpenGL->MatrixMultiply(modmatrix_7, rotacionYmod_7, modmatrix_7);
	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix_7);
	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"colorText", 27);
	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"normText", 28);
	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"specText", 29);
	m_ModeloShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	float campos_7[3] = { m_Camera->GetXPos(), m_Camera->GetYPos(), m_Camera->GetZPos() };
	m_ModeloShader->PonVec3(m_OpenGL, (char*)"camaraDir", campos_7);
	m_ModeloShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	casaP3->Render(m_OpenGL);*/

#pragma endregion

#pragma region CasaParte4

	/*m_ModeloShader->SetShader(m_OpenGL);
	float modmatrix_8[16];
	float rotacionYmod_8[16];
	m_OpenGL->GetWorldMatrix(modmatrix_8);
	m_OpenGL->MatrixTranslation(modmatrix_8, casaP4->x, casaP4->y, casaP4->z);
	m_OpenGL->MatrixRotationY(rotacionYmod_8, 0.0);
	m_OpenGL->MatrixMultiply(modmatrix_8, rotacionYmod_8, modmatrix_8);
	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix_8);
	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"colorText", 30);
	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"normText", 31);
	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"specText", 32);
	m_ModeloShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	float campos_8[3] = { m_Camera->GetXPos(), m_Camera->GetYPos(), m_Camera->GetZPos() };
	m_ModeloShader->PonVec3(m_OpenGL, (char*)"camaraDir", campos_8);
	m_ModeloShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	casaP4->Render(m_OpenGL);*/

#pragma endregion

#pragma region CasaParte5

	/*m_ModeloShader->SetShader(m_OpenGL);
	float modmatrix_9[16];
	float rotacionYmod_9[16];
	m_OpenGL->GetWorldMatrix(modmatrix_9);
	m_OpenGL->MatrixTranslation(modmatrix_9, casaP5->x, casaP5->y, casaP5->z);
	m_OpenGL->MatrixRotationY(rotacionYmod_9, 0.0);
	m_OpenGL->MatrixMultiply(modmatrix_9, rotacionYmod_9, modmatrix_9);
	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix_9);
	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_ModeloShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"colorText", 33);
	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"normText", 34);
	m_ModeloShader->Pon1Entero(m_OpenGL, (char*)"specText", 35);
	m_ModeloShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	float campos_9[3] = { m_Camera->GetXPos(), m_Camera->GetYPos(), m_Camera->GetZPos() };
	m_ModeloShader->PonVec3(m_OpenGL, (char*)"camaraDir", campos_9);
	m_ModeloShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	casaP5->Render(m_OpenGL);*/

#pragma endregion

#pragma region mar

	glEnable(GL_BLEND);
	glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA);

	//m_OpenGL->MatrixTranslation(worldMatrixBill, mar->x, terreno->Superficie(mar->x, mar->z) + 9, mar->z);

	static float oleaje = 0;
	oleaje += 0.00040;
	if (oleaje > 100) {
		oleaje = 0;
	}

	m_AguaShader->SetShader(m_OpenGL);
	float modmatrix_10[16]{};
	float rotacionYmod_10[16]{};
	m_OpenGL->GetWorldMatrix(modmatrix_10);
	m_OpenGL->MatrixTranslation(modmatrix_10, mar->x, mar->y, mar->z);
	m_OpenGL->MatrixRotationY(rotacionYmod_10, 0.0);
	m_OpenGL->MatrixMultiply(modmatrix_10, rotacionYmod_10, modmatrix_10);
	m_AguaShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix_10);
	m_AguaShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_AguaShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_AguaShader->Pon1Entero(m_OpenGL, (char*)"shaderTexture", 36);
	m_AguaShader->Pon1Entero(m_OpenGL, (char*)"shaderTextureN", 37);
	m_AguaShader->Pon1Entero(m_OpenGL, (char*)"shaderTextureSp", 38);
	m_AguaShader->Pon1Flotante(m_OpenGL, (char*)"shininess", 30.0f);
	m_AguaShader->Pon1Flotante(m_OpenGL, (char*)"factAtAmb", factAtAmb);
	m_AguaShader->Pon1Flotante(m_OpenGL, (char*)"factAtDif", factAtDif);
	m_AguaShader->Pon1Flotante(m_OpenGL, (char*)"factAtSpec", factAtSpec);
	m_AguaShader->Pon1Flotante(m_OpenGL, (char*)"movimiento", oleaje);
	m_AguaShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	float camaraDir[3] = { m_Camera->GetXPos(), m_Camera->GetYPos(), m_Camera->GetZPos() };
	m_AguaShader->PonVec3(m_OpenGL, (char*)"camaraDir", camaraDir);
	m_AguaShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	mar->Render(m_OpenGL);

	glDisable(GL_BLEND);
#pragma endregion


#pragma region carga palmera

	/*for (int k = 0; k < 20; k++)
	{
		palmera->x = palmXZ[k][0];
		palmera->z = palmXZ[k][1];
		m_OpenGL->MatrixTranslation(worldMatrixBill, palmera->x + 0.2, terreno->Superficie(palmera->x, palmera->z) - 2, palmera->z + 0.2);
		float rotaypalmera1[16];
		m_OpenGL->MatrixRotationY(rotaypalmera1, -palmera->angBill(m_Camera->GetXPos(), m_Camera->GetZPos()));
		m_OpenGL->MatrixMultiply(worldMatrixBill, rotaypalmera1, worldMatrixBill);
		m_VeggieShader->SetShader(m_OpenGL);
		m_VeggieShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
		m_VeggieShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_VeggieShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_VeggieShader->Pon1Entero(m_OpenGL, (char*)"billtext", 50);
		m_VeggieShader->Pon1Entero(m_OpenGL, (char*)"billnorm", 51);
		m_VeggieShader->Pon1Flotante(m_OpenGL, (char*)"factAtDif", factAtDif);
		m_VeggieShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_VeggieShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		palmera->Render(m_OpenGL);
	}*/
#pragma endregion
#pragma region carga pasto 
	/*for (int k = 0; k < 20; k++)
	{
		pasto->x = pastoXZ[k][0];
		pasto->z = pastoXZ[k][1];
		m_OpenGL->MatrixTranslation(worldMatrixBill, pasto->x + 0.2, terreno->Superficie(pasto->x, pasto->z) - 2, pasto->z + 0.2);
		float rotaypasto[16];
		m_OpenGL->MatrixRotationY(rotaypasto, -pasto->angBill(m_Camera->GetXPos(), m_Camera->GetZPos()));
		m_OpenGL->MatrixMultiply(worldMatrixBill, rotaypasto, worldMatrixBill);
		m_VeggieShader->SetShader(m_OpenGL);
		m_VeggieShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
		m_VeggieShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_VeggieShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_VeggieShader->Pon1Entero(m_OpenGL, (char*)"billtext", 39);
		m_VeggieShader->Pon1Entero(m_OpenGL, (char*)"billnorm", 40);
		m_VeggieShader->Pon1Flotante(m_OpenGL, (char*)"factAtDif", factAtDif);
		m_VeggieShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_VeggieShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		pasto->Render(m_OpenGL);
	}*/
#pragma endregion 

#pragma region carga rocas

	/*m_OpenGL->MatrixTranslation(worldMatrixBill, rocastnd->x + 0.2, terreno->Superficie(rocastnd->x, rocastnd->z) - 2, rocastnd->z + 0.2);
	float rotaypasto[16];
	m_OpenGL->MatrixRotationY(rotaypasto, -rocastnd->angBill(m_Camera->GetXPos(), m_Camera->GetZPos()));
	m_OpenGL->MatrixMultiply(worldMatrixBill, rotaypasto, worldMatrixBill);
	m_VeggieShader->SetShader(m_OpenGL);
	m_VeggieShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
	m_VeggieShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	m_VeggieShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	m_VeggieShader->Pon1Entero(m_OpenGL, (char*)"billtext", 41);
	m_VeggieShader->Pon1Entero(m_OpenGL, (char*)"billnorm", 42);
	m_VeggieShader->Pon1Flotante(m_OpenGL, (char*)"factAtDif", factAtDif);
	m_VeggieShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	m_VeggieShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	rocastnd->Render(m_OpenGL);*/
#pragma endregion


	// Present the rendered scene to the screen.
	m_OpenGL->EndScene();


	return true;
}
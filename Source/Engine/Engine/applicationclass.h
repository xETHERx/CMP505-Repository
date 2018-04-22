////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "inputclass.h"
#include "d3dclass.h"
#include "cameraclass.h"
#include "terrainclass.h"
#include "colorshaderclass.h"
#include "timerclass.h"
#include "positionclass.h"
#include "fpsclass.h"
#include "cpuclass.h"
#include "fontshaderclass.h"
#include "textclass.h"
#include "skydomeclass.h"
#include "skydomeshaderclass.h"
#include "skyplaneclass.h"
#include "skyplaneshaderclass.h"
#include "modelclass.h"
#include "bitmapclass.h"
#include "soundclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ApplicationClass
////////////////////////////////////////////////////////////////////////////////
class ApplicationClass
{
public:
	ApplicationClass();
	ApplicationClass(const ApplicationClass&);
	~ApplicationClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

private:
	bool HandleInput(float);
	bool RenderGraphics();

	void Collisiondetect();

private:
	InputClass* m_Input;
	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	TerrainClass* m_Terrain;
	ColorShaderClass* m_ColorShader;
	TimerClass* m_Timer;
	PositionClass* m_Position, *m_pos1, *m_pos2;
	FpsClass* m_Fps;
	CpuClass* m_Cpu;
	FontShaderClass* m_FontShader;
	TextClass* m_Text;

	SkyDomeClass* m_SkyDome;
	SkyDomeShaderClass* m_SkyDomeShader;

	SkyPlaneClass *m_SkyPlane;
	SkyPlaneShaderClass* m_SkyPlaneShader;

	ModelClass *m_model, *m_model2;

	BitmapClass* m_Minimap, *m_Minibox01, *m_Minibox02,*m_Player;

	bool boxcollisionX, boxcollisionZ;
	bool xp, xn, zp, zn, xp2, xn2, zp2, zn2;
	bool m_win;
	float movement, movement2;
	int m_width, m_height;
};

#endif
////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "applicationclass.h"


ApplicationClass::ApplicationClass()
{
	m_Input = 0;//
	m_Direct3D = 0;//
	m_Camera = 0;//
	m_Terrain = 0;//
	m_TerrainShader = 0;//
	m_ColorShader = 0;//
	m_Timer = 0;//
	m_Position = 0;//
	m_Fps = 0;//
	m_Cpu = 0;//
	m_FontShader = 0;//
	m_Text = 0;//

	m_SkyDome = 0;//
	m_SkyDomeShader = 0;//

	m_SkyPlane = 0;//
	m_SkyPlaneShader = 0;//

	m_model = 0;
	m_model2 = 0;

	m_Minibox01 = 0;//
	m_Minibox02 = 0;//
	m_Player = 0;//
	m_Minimap = 0;//
	m_BitMap = 0;//

	m_sound = 0;
	m_sound2 = 0;

	m_TextureShader = 0;//



	m_pos1 = 0;//
	m_pos2 = 0;//

	boxcollisionX = false;
	boxcollisionZ = false;

	xp = false;
	xn = false;
	zp = false;
	zn = false;
	xp2 = false;
	xn2 = false;
	zp2 = false;
	zn2 = false;
	m_win = false;
	movement = 0;
	movement2 = 0;

	m_Light = 0;//
	m_lightshader = 0;//
	m_DepthShader = 0;
	m_ShadowShader = 0;
	m_RenderTexture = 0;
}


ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}


ApplicationClass::~ApplicationClass()
{
}


bool ApplicationClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;
	float cameraX, cameraY, cameraZ;

	char videoCard[128];
	int videoMemory;

	m_width = screenWidth;
	m_height = screenHeight;

	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_Direct3D = new D3DClass;
	if (!m_Direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize DirectX 11.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Set the initial position of the camera.
	cameraX = 50.0f;
	cameraY = 100.0f;
	cameraZ = 50.0f;

	m_Camera->SetPosition(cameraX, cameraY, cameraZ);

	// Create the terrain object.
	m_Terrain = new TerrainClass;
	if (!m_Terrain)
	{
		return false;
	}

	// Initialize the terrain object.
	result = m_Terrain->InitializeTerrain(m_Direct3D->GetDevice(), 129, 129, L"../Engine/data/colorm01.bmp");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	m_TerrainShader = new TerrainShaderClass;
	if (!m_TerrainShader)
	{
		return false;
	}

	result = m_TerrainShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		return false;
	}

	// Create the color shader object.
	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position of the viewer to the same as the initial camera position.
	m_Position->SetPosition(cameraX, cameraY, cameraZ);

	// Create the fps object.
	m_Fps = new FpsClass;
	if (!m_Fps)
	{
		return false;
	}

	// Initialize the fps object.
	m_Fps->Initialize();

	// Create the cpu object.
	m_Cpu = new CpuClass;
	if (!m_Cpu)
	{
		return false;
	}

	// Initialize the cpu object.
	m_Cpu->Initialize();

	// Create the font shader object.
	m_FontShader = new FontShaderClass;
	if (!m_FontShader)
	{
		return false;
	}

	// Initialize the font shader object.
	result = m_FontShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	// Retrieve the video card information.
	m_Direct3D->GetVideoCardInfo(videoCard, videoMemory);

	// Set the video card information in the text object.
	result = m_Text->SetVideoCardInfo(videoCard, videoMemory, m_Direct3D->GetDeviceContext());
	if (!result)
	{
		MessageBox(hwnd, L"Could not set video card info in the text object.", L"Error", MB_OK);
		return false;
	}

	//Create and initialize both the SkyDomeClass
	//and SkyDomeShaderClass objects here.
	/////////////////////////////////////
	// Create the sky dome object.
	/////////////////////////////////////

	m_SkyDome = new SkyDomeClass;
	if (!m_SkyDome)
	{
		return false;
	}

	// Initialize the sky dome object.
	result = m_SkyDome->Initialize(m_Direct3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);
		return false;
	}

	// Create the sky dome shader object.
	m_SkyDomeShader = new SkyDomeShaderClass;
	if (!m_SkyDomeShader)
	{
		return false;
	}

	// Initialize the sky dome shader object.
	result = m_SkyDomeShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome shader object.", L"Error", MB_OK);
		return false;
	}
	///////////////////////////////////////
	// Create the sky plane object.
	////////////////////////////////////////

	m_SkyPlane = new SkyPlaneClass;
	if (!m_SkyPlane)
	{
		return false;
	}

	// Initialize the sky plane object.
	result = m_SkyPlane->Initialize(m_Direct3D->GetDevice(), L"../Engine/data/cloud001.dds", L"../Engine/data/cloud002.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky plane object.", L"Error", MB_OK);
		return false;
	}

	// Create the sky plane shader object.
	m_SkyPlaneShader = new SkyPlaneShaderClass;
	if (!m_SkyPlaneShader)
	{
		return false;
	}

	// Initialize the sky plane shader object.
	result = m_SkyPlaneShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky plane shader object.", L"Error", MB_OK);
		return false;
	}

	/////////////////////////////
	// Create the Minimap objects.
	/////////////////////////////

	m_BitMap = new BitmapClass;
	if (!m_BitMap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_BitMap->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, L"../Engine/data/youwin.dds", 700, 700);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the m_BitMap object.", L"Error", MB_OK);
		return false;
	}

	m_Minimap = new BitmapClass;
	if (!m_Minimap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Minimap->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, L"../Engine/data/minimap.dds", 258, 258);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Minimap object.", L"Error", MB_OK);
		return false;
	}
	//minimap_box01
	m_Minibox01 = new BitmapClass;
	if (!m_Minibox01)
	{
		return false;
	}

	result = m_Minibox01->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, L"../Engine/data/Box.dds", 8, 8);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the m_Minibox01 object.", L"Error", MB_OK);
		return false;
	}

	//minimap_box02
	m_Minibox02 = new BitmapClass;
	if (!m_Minibox02)
	{
		return false;
	}

	result = m_Minibox02->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, L"../Engine/data/Box02.dds", 8, 8);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the m_Minibox02 object.", L"Error", MB_OK);
		return false;
	}


	//minimap_Player
	m_Player = new BitmapClass;
	if (!m_Player)
	{
		return false;
	}

	result = m_Player->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight, L"../Engine/data/Playericon.dds", 12, 12);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the m_Player object.", L"Error", MB_OK);
		return false;
	}

	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	result = m_TextureShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		return false;
	}

	////////////////////////////////
	// Initialize the model object.
	////////////////////////////////
	m_model = new ModelClass;
	if (!m_model)
	{
		return false;
	}

	result = m_model->Initialize(m_Direct3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Box.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_model2 = new ModelClass;
	if (!m_model2)
	{
		return false;
	}

	result = m_model2->Initialize(m_Direct3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Box02.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model2 object.", L"Error", MB_OK);
		return false;
	}


	// Initialize the light object.
	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.3f, 0.3f, 0.3f, 1.0f);
	m_Light->SetDiffuseColor(0.5f, 0.5f, 0.5f, 0.5f);
	m_Light->SetDirection(0.0f, -1.0f, -1.0f);
	m_Light->SetLookAt(0, -1, -1);
	m_Light->GenerateProjectionMatrix(SCREEN_DEPTH, SCREEN_NEAR);


	m_lightshader = new LightShaderClass;
	if (!m_lightshader)
	{
		return false;
	}
	//m_Light->GenerateProjectionMatrix(SCREEN_DEPTH, SCREEN_NEAR);

	result = m_lightshader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		return false;
	}

	// Create the depth shader object.
	m_DepthShader = new DepthShaderClass;
	if (!m_DepthShader)
	{
		return false;
	}

	// Initialize the depth shader object.
	result = m_DepthShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the depth shader object.", L"Error", MB_OK);
		return false;
	}


	///////////////
	//Box Position
	///////////////
	m_pos1 = new PositionClass;
	if (!m_pos1)
	{
		return false;
	}
	m_pos1->SetPosition(65, 0, 65);

	m_pos2 = new PositionClass;
	if (!m_pos2)
	{
		return false;
	}
	m_pos2->SetPosition(65, 0, 57);

	/////////////////////
	//sound            //
	/////////////////////

	// Initialize the Direct3D object.

	m_sound = new SoundClass;
	if (!m_sound)
	{
		return false;
	}

	result = m_sound->Initialize(hwnd, "../Engine/data/pushbox.wav");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize m_sound.", L"Error", MB_OK);
		return false;
	}

	m_sound2 = new SoundClass;
	if (!m_sound2)
	{
		return false;
	}

	result = m_sound2->Initialize(hwnd, "../Engine/data/Victory.wav");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize m_sound2.", L"Error", MB_OK);
		return false;
	}

	// Create the render to texture object.
	m_RenderTexture = new RenderTextureClass;
	if (!m_RenderTexture)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_RenderTexture->Initialize(m_Direct3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the render to texture object.", L"Error", MB_OK);
		return false;
	}

	m_ShadowShader = new ShadowShaderClass;
	if (!m_ShadowShader)
	{
		return false;
	}

	result = m_ShadowShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		return false;
	}
	return true;


}



void ApplicationClass::Shutdown()
{
	// Release the render to texture object.
	if (m_RenderTexture)
	{
		m_RenderTexture->Shutdown();
		delete m_RenderTexture;
		m_RenderTexture = 0;
	}

	if (m_ShadowShader)
	{
		m_ShadowShader->Shutdown();
		delete m_ShadowShader;
		m_ShadowShader = 0;
	}


	if (m_DepthShader)
	{
		m_DepthShader->Shutdown();
		delete m_DepthShader;
		m_DepthShader = 0;
	}

	if (m_sound)
	{
		m_sound->Shutdown();
		delete m_sound;
		m_sound = 0;
	}

	if (m_sound2)
	{
		m_sound2->Shutdown();
		delete m_sound2;
		m_sound2 = 0;
	}

	if (m_pos1)
	{
		delete m_pos1;
		m_pos1 = 0;
	}

	if (m_pos2)
	{
		delete m_pos2;
		m_pos2 = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_lightshader)
	{
		m_lightshader->Shutdown();
		delete m_lightshader;
		m_lightshader = 0;
	}

	// Release the model object.
	if (m_model)
	{
		m_model->Shutdown();
		delete m_model;
		m_model = 0;
	}

	if (m_model2)
	{
		m_model2->Shutdown();
		delete m_model2;
		m_model2 = 0;
	}

	// Release the Minimap objects.
	if (m_Minimap)
	{
		m_Minimap->Shutdown();
		delete m_Minimap;
		m_Minimap = 0;
	}
	// Release the sky plane shader object.
	if (m_SkyPlaneShader)
	{
		m_SkyPlaneShader->Shutdown();
		delete m_SkyPlaneShader;
		m_SkyPlaneShader = 0;
	}

	// Release the sky plane object.
	if (m_SkyPlane)
	{
		m_SkyPlane->Shutdown();
		delete m_SkyPlane;
		m_SkyPlane = 0;
	}
	// Release the sky dome shader object.
	if (m_SkyDomeShader)
	{
		m_SkyDomeShader->Shutdown();
		delete m_SkyDomeShader;
		m_SkyDomeShader = 0;
	}

	// Release the sky dome object.
	if (m_SkyDome)
	{
		m_SkyDome->Shutdown();
		delete m_SkyDome;
		m_SkyDome = 0;
	}

	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the font shader object.
	if (m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	// Release the cpu object.
	if (m_Cpu)
	{
		m_Cpu->Shutdown();
		delete m_Cpu;
		m_Cpu = 0;
	}

	// Release the fps object.
	if (m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}

	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the color shader object.
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// Release the terrain object.
	if (m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}

	if (m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		delete m_TerrainShader;
		m_TerrainShader = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the Direct3D object.
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	// Release the input object.
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}


bool ApplicationClass::Frame()
{
	static float lightPositionX = -5.0f;
	bool result;

	Collisiondetect();

	// Read the user input.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Update the system stats.
	m_Timer->Frame();
	m_Fps->Frame();
	m_Cpu->Frame();

	// Update the FPS value in the text object.
	result = m_Text->SetFps(m_Fps->GetFps(), m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Update the CPU usage value in the text object.
	result = m_Text->SetCpu(m_Cpu->GetCpuPercentage(), m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Do the frame input processing.
	result = HandleInput(m_Timer->GetTime());
	if (!result)
	{
		return false;
	}

	// Do the sky plane frame processing.
	m_SkyPlane->Frame();

	// Render the graphics.
	result = RenderGraphics();
	if (!result)
	{
		return false;
	}

	// Update the position of the light each frame.
	//lightPositionX += 0.05f;
	//if (lightPositionX > 5.0f)
	//{
	//	lightPositionX = -5.0f;
	//}

	// Update the position of the light.
	m_Light->SetPosition(0, 200.0f, -5.0f);

	// Render the graphics scene.
	result = RenderGraphics();
	if (!result)
	{
		return false;
	}

	return result;
}


bool ApplicationClass::HandleInput(float frameTime)
{
	bool keyDown, result;
	float posX, posY, posZ, rotX, rotY, rotZ;
	int mousex, mousey;
	D3DXVECTOR3 camPos, boxPos1, boxPos2;

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	m_Position->GetPosition(camPos.x, camPos.y, camPos.z);
	m_pos1->GetPosition(boxPos1.x, boxPos1.y, boxPos1.z);
	m_pos2->GetPosition(boxPos2.x, boxPos2.y, boxPos2.z);
	if (!m_win)
	{
		// Handle the input.
		if (!(camPos.x - boxPos1.x <= 4 && camPos.x - boxPos1.x >= -4
			&& camPos.z - boxPos1.z <= 4 && camPos.z - boxPos1.z >= -4) &&
			!(camPos.x - boxPos2.x <= 4 && camPos.x - boxPos2.x >= -4
				&& camPos.z - boxPos2.z <= 4 && camPos.z - boxPos2.z >= -4))
		{
			keyDown = m_Input->IsUpPressed();
			m_Position->MoveForward(keyDown);

			m_Input->GetMouseLocation(mousex, mousey);
			m_Position->Rotate((float)mousex, (float)mousey);

		}
		keyDown = m_Input->IsDownPressed();
		m_Position->MoveBackward(keyDown);
	}

	if (keyDown = m_Input->IsRPressed())
	{
		m_win = false;
		m_pos1->SetPosition(65, 0, 65);
		m_pos2->SetPosition(65, 0, 57);
		m_Position->SetPosition(50, 10, 50);
	}
	

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	// Update the position values in the text object.
	result = m_Text->SetCameraPosition(posX, posY, posZ, m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Update the rotation values in the text object.
	result = m_Text->SetCameraRotation(rotX, rotY, rotZ, m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}


	return true;
}


bool ApplicationClass::RenderGraphics()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, lightViewMatrix, lightProjectionMatrix;
	D3DXVECTOR3 cameraPosition, boxpos1;
	bool result, foundHeight;
	float height, posX, posY, posZ;

	result = RenderSceneToTexture();
	if (!result)
	{
		return false;
	}
	// Clear the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);
	m_Light->GetViewMatrix(lightViewMatrix);
	m_Light->GetProjectionMatrix(lightProjectionMatrix);

	m_Position->GetPosition(cameraPosition.x, cameraPosition.y, cameraPosition.z);
	foundHeight = m_Terrain->GetHeightAtPosition(cameraPosition.x, cameraPosition.z, height);

	if (foundHeight)
	{
		m_Position->SetPosition(cameraPosition.x, height + 2, cameraPosition.z);

	}

	

	/////////////////
	//Render skybox//
	/////////////////

	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();

	// Translate the sky dome to be centered around the camera position.
	D3DXMatrixTranslation(&worldMatrix, cameraPosition.x, cameraPosition.y, cameraPosition.z);
	//Before rendering the sky dome we turn off both back face culling and the Z buffer.

	// Turn off back face culling.
	m_Direct3D->TurnOffCulling();

	// Turn off the Z buffer.
	m_Direct3D->TurnZBufferOff();
	//We then render the sky dome using the sky dome shader.

	// Render the sky dome using the sky dome shader.
	m_SkyDome->Render(m_Direct3D->GetDeviceContext());
	m_SkyDomeShader->Render(m_Direct3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());
	//Once rendering is complete we turn back face culling and the Z buffer on again and resume rendering the rest of the scene as normal.

	// Turn back face culling back on.
	m_Direct3D->TurnOnCulling();

	// Turn the Z buffer back on.
	m_Direct3D->TurnZBufferOn();

	// Reset the world matrix.
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// Render the terrain buffers.
	m_Terrain->Render(m_Direct3D->GetDeviceContext());

	// Render the terrain using the terrain shader.
	result = m_ShadowShader->Render(m_Direct3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
		lightProjectionMatrix, m_Terrain->GetTexture(), m_RenderTexture->GetShaderResourceView(), m_Light->GetPosition(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}


	//////////
	//shadow//
	//////////


	//// Setup the translation matrix for the cube model.
	//m_pos1->GetPosition(posX, posY, posZ);
	//D3DXMatrixTranslation(&worldMatrix, posX, posY, posZ);

	//// Put the cube model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_model->Render(m_Direct3D->GetDeviceContext());

	//// Render the model using the shadow shader.
	//
	////box2

	//// Reset the world matrix.
	//m_Direct3D->GetWorldMatrix(worldMatrix);

	//// Setup the translation matrix for the sphere model.
	//m_pos2->GetPosition(posX, posY, posZ);
	//D3DXMatrixTranslation(&worldMatrix, posX, posY, posZ);

	//// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_model2->Render(m_Direct3D->GetDeviceContext());

	//if (!result)
	//{
	//	return false;
	//}


	D3DXMATRIX rotationMatrix, translationMatrix, scaleMatrix;
	D3DXVECTOR3 boxPos1, boxPos2, cameraPos;

	//box1
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_pos1->GetPosition(boxPos1.x, boxPos1.y, boxPos1.z);
	foundHeight = m_Terrain->GetHeightAtPosition(boxPos1.x, boxPos1.z, height);

	if (foundHeight)
	{
		m_pos1->SetPosition(boxPos1.x, height + 1, boxPos1.z);

	}

	//m_pos1->GetPosition(cameraPos.x, cameraPos.y, cameraPos.z);
	//D3DXMatrixRotationY(&rotationMatrix, 60.0f*3.14f / 180.0f);

	//D3DXMatrixScaling(&scaleMatrix, 20, 3, 3);

	D3DXMatrixTranslation(&translationMatrix, boxPos1.x, boxPos1.y, boxPos1.z);

	//worldMatrix = scaleMatrix *translationMatrix * rotationMatrix;

	worldMatrix = translationMatrix;

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_model->Render(m_Direct3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_ShadowShader->Render(m_Direct3D->GetDeviceContext(), m_model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
		lightProjectionMatrix, m_model->GetTexture(), m_RenderTexture->GetShaderResourceView(), m_Light->GetPosition(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());

	if (!result)
	{
		return false;
	}


	//box2
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_pos2->GetPosition(boxPos2.x, boxPos2.y, boxPos2.z);

	foundHeight = m_Terrain->GetHeightAtPosition(boxPos2.x, boxPos2.z, height);

	if (foundHeight)
	{
		m_pos2->SetPosition(boxPos2.x, height + 1, boxPos2.z);

	}

	D3DXMatrixTranslation(&translationMatrix, boxPos2.x, boxPos2.y, boxPos2.z);
	//D3DXMatrixRotationYawPitchRoll(&rotation, yaw, pitch, roll);
	worldMatrix = translationMatrix;
	m_model2->Render(m_Direct3D->GetDeviceContext());

	result = m_ShadowShader->Render(m_Direct3D->GetDeviceContext(), m_model2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
		lightProjectionMatrix, m_model2->GetTexture(), m_RenderTexture->GetShaderResourceView(), m_Light->GetPosition(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}

	m_Direct3D->GetWorldMatrix(worldMatrix);

	////////////////
	//render cloud//
	////////////////

	// Enable additive blending so the clouds blend with the sky dome color.
	m_Direct3D->EnableSecondBlendState();

	// Render the sky plane using the sky plane shader.
	m_SkyPlane->Render(m_Direct3D->GetDeviceContext());
	m_SkyPlaneShader->Render(m_Direct3D->GetDeviceContext(), m_SkyPlane->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_SkyPlane->GetCloudTexture1(), m_SkyPlane->GetCloudTexture2(), m_SkyPlane->GetTranslation(0), m_SkyPlane->GetTranslation(1),
		m_SkyPlane->GetTranslation(2), m_SkyPlane->GetTranslation(3), m_SkyPlane->GetBrightness());

	// Turn off the Z buffer to begin all 2D rendering.
	m_Direct3D->TurnZBufferOff();

	// Turn on the alpha blending before rendering the text.
	m_Direct3D->TurnOnAlphaBlending();

	// Render the text user interface elements.
	result = m_Text->Render(m_Direct3D->GetDeviceContext(), m_FontShader, worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_Direct3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_Direct3D->TurnZBufferOn();

#
	//We now also get the ortho matrix from the D3DClass 
	//for 2D rendering.We will pass this in instead of the projection matrix.


	////////////////////
	//render minimap
	////////////////////
	m_Direct3D->GetOrthoMatrix(orthoMatrix);
	//The Z buffer is turned off before we do any 2D rendering.

	m_Direct3D->TurnZBufferOff();

	result = m_Minimap->Render(m_Direct3D->GetDeviceContext(), m_width - 300, m_height - 1025);
	if (!result)
	{
		return false;
	}

	result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Minimap->GetIndexCount(),
		worldMatrix, baseViewMatrix, orthoMatrix, m_Minimap->GetTexture());
	if (!result)
	{
		return false;
	}

	////////////////////
	//Minimap_boxes //
	////////////////////

	result = m_Minibox01->Render(m_Direct3D->GetDeviceContext(), (boxPos1.x * 2) + 4 + m_width - 300, (boxPos1.z * 2) + 4 + m_height - 1025);
	if (!result)
	{
		return false;
	}

	result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Minibox01->GetIndexCount(),
		worldMatrix, baseViewMatrix, orthoMatrix, m_Minibox01->GetTexture());
	if (!result)
	{
		return false;
	}


	//box02_minimap

	result = m_Minibox02->Render(m_Direct3D->GetDeviceContext(), (boxPos2.x * 2) + 4 + m_width - 300, (boxPos2.z * 2) + 4 + m_height - 1025);
	if (!result)
	{
		return false;
	}

	result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Minibox02->GetIndexCount(),
		worldMatrix, baseViewMatrix, orthoMatrix, m_Minibox02->GetTexture());
	if (!result)
	{
		return false;
	}

	//player_minimap
	m_Position->GetPosition(cameraPos.x, cameraPos.y, cameraPos.z);
	result = m_Player->Render(m_Direct3D->GetDeviceContext(), cameraPos.x * 2 + 4 + m_width - 300, cameraPos.z * 2 + 4 + m_height - 1025);
	//result = m_Player->Render(m_Direct3D->GetDeviceContext(), cameraPos.x * 2 + 10, cameraPos.z * 2 + 10);
	if (!result)
	{
		return false;
	}

	result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Player->GetIndexCount(),
		worldMatrix, baseViewMatrix, orthoMatrix, m_Player->GetTexture());
	if (!result)
	{
		return false;
	}


	m_Direct3D->TurnZBufferOn();


	if (m_win) {

		m_Direct3D->TurnZBufferOff();

		// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
		result = m_BitMap->Render(m_Direct3D->GetDeviceContext(), m_width / 2 - 400, m_height / 2 - 400);
		if (!result)
		{
			return false;
		}
		//Once the vertex / index buffers are prepared we draw them using the texture shader.Notice we send in the orthoMatrix instead of the projectionMatrix for rendering 2D.Due note also that if your view matrix is changing you will need to create a default one for 2D rendering and use it instead of the regular view matrix.In this tutorial using the regular view matrix is fine as the camera in this tutorial is stationary.

		// Render the bitmap with the texture shader.
		result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_BitMap->GetIndexCount(),
			worldMatrix, baseViewMatrix, orthoMatrix, m_BitMap->GetTexture());
		if (!result)
		{
			return false;
		}
		//After all the 2D rendering is done we turn the Z buffer back on for the next round of 3D rendering.

		// Turn the Z buffer back on now that all 2D rendering has completed.
		m_Direct3D->TurnZBufferOn();

		//////////////////////////////////////////////////////////
	}
	//push box_1
	if (xp)
	{
		m_pos1->SetPosition(boxPos1.x + 0.5f, boxPos1.y, boxPos1.z);
		movement += 0.5f;
	}
	if (xn)
	{
		m_pos1->SetPosition(boxPos1.x - 0.5f, boxPos1.y, boxPos1.z);
		movement += 0.5f;
	}
	if (zp)
	{
		m_pos1->SetPosition(boxPos1.x, boxPos1.y, boxPos1.z + 0.5f);
		movement += 0.5f;
	}
	if (zn)
	{
		m_pos1->SetPosition(boxPos1.x, boxPos1.y, boxPos1.z - 0.5f);
		movement += 0.5f;
	}

	if (movement >= 4)
	{
		movement = 0;
		xp = false;
		xn = false;
		zp = false;
		zn = false;
	}

	//push box_2
	if (xp2)
	{
		m_pos2->SetPosition(boxPos2.x + 0.5f, boxPos2.y, boxPos2.z);
		movement2 += 0.5f;
	}
	if (xn2)
	{
		m_pos2->SetPosition(boxPos2.x - 0.5f, boxPos2.y, boxPos2.z);
		movement2 += 0.5f;
	}
	if (zp2)
	{
		m_pos2->SetPosition(boxPos2.x, boxPos2.y, boxPos2.z + 0.5f);
		movement2 += 0.5f;
	}
	if (zn2)
	{
		m_pos2->SetPosition(boxPos2.x, boxPos2.y, boxPos2.z - 0.5f);
		movement2 += 0.5f;
	}

	if (movement2 >= 4)
	{
		movement2 = 0;
		xp2 = false;
		xn2 = false;
		zp2 = false;
		zn2 = false;
	}
	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}

void ApplicationClass::Collisiondetect()
{
	D3DXVECTOR3 cameraPos, box1Pos, box2Pos;

	m_Position->GetPosition(cameraPos.x, cameraPos.y, cameraPos.z);
	m_pos1->GetPosition(box1Pos.x, box1Pos.y, box1Pos.z);
	m_pos2->GetPosition(box2Pos.x, box2Pos.y, box2Pos.z);

	//betweenbox
	if ((box1Pos.x - box2Pos.x) <= 4 && (box1Pos.x - box2Pos.x) >= -4 && (box1Pos.z - box2Pos.z) <= 4 && (box1Pos.z - box2Pos.z) >= -4)
	{
		if (abs(box2Pos.x - box1Pos.x) > abs(box2Pos.z - box1Pos.z))
		{
			boxcollisionX = true;
		}
		if (abs(box2Pos.x - box1Pos.x) < abs(box2Pos.z - box1Pos.z))
		{
			boxcollisionZ = true;
		}
	}
	else
	{
		boxcollisionX = false;
		boxcollisionZ = false;
	}



	//camera-1
	if (cameraPos.x - box1Pos.x <= 4 && cameraPos.x - box1Pos.x >= -4
		&& cameraPos.z - box1Pos.z <= 4 && cameraPos.z - box1Pos.z >= -4)
	{


		//x axis
		if (abs(cameraPos.x - box1Pos.x) > abs(cameraPos.z - box1Pos.z) && !boxcollisionX)
		{
			//x+
			if (box1Pos.x > cameraPos.x)
			{
				m_sound->PlayWaveFile();
				xp = true;
				//m_pos1->SetPosition(box1Pos.x + 10, box1Pos.y, box1Pos.z);
			}
			//x-
			if (box1Pos.x < cameraPos.x)
			{
				m_sound->PlayWaveFile();
				xn = true;
				//m_pos1->SetPosition(box1Pos.x - 10, box1Pos.y, box1Pos.z);
			}
		}


		//z axis
		if (abs(cameraPos.x - box1Pos.x) < abs(cameraPos.z - box1Pos.z) && !boxcollisionZ)
		{
			//z+
			if (box1Pos.z > cameraPos.z)
			{
				m_sound->PlayWaveFile();
				zp = true;
				//m_pos1->SetPosition(box1Pos.x, box1Pos.y, box1Pos.z + 10);
			}
			//z-
			if (box1Pos.z < cameraPos.z)
			{
				m_sound->PlayWaveFile();
				zn = true;
				//m_pos1->SetPosition(box1Pos.x, box1Pos.y, box1Pos.z - 10);
			}


		}
	}

	//camera-2
	//Box2 Collision detection
	if (cameraPos.x - box2Pos.x <= 4 && cameraPos.x - box2Pos.x >= -4
		&& cameraPos.z - box2Pos.z <= 4 && cameraPos.z - box2Pos.z >= -4)
	{

		//Moving direction
		//x axis
		if (abs(cameraPos.x - box2Pos.x) > abs(cameraPos.z - box2Pos.z) && !boxcollisionX)
		{


			//x+
			if (box2Pos.x > cameraPos.x)
			{
				xp2 = true;
				m_sound->PlayWaveFile();
			}
			//x-

			if (box2Pos.x < cameraPos.x)
			{
				xn2 = true;
				m_sound->PlayWaveFile();
			}

		}

		//z axis
		if (abs(cameraPos.x - box2Pos.x) < abs(cameraPos.z - box2Pos.z) && !boxcollisionZ)
		{

			////betweenBox
			//if (abs(box2Pos.z - box1Pos.z) <= 0)
			//{
			//	zp2 = false;
			//	zn2 = false;

			//}

			//z+
			if (box2Pos.z > cameraPos.z)
			{
				zp2 = true;
				m_sound->PlayWaveFile();
			}
			//z-
			if (box2Pos.z < cameraPos.z)
			{
				zn2 = true;
				m_sound->PlayWaveFile();
			}
		}
	}

	if (box1Pos.x >=14&&box1Pos.x<=28 && box1Pos.z >=100 && box1Pos.z<=114 && box2Pos.z >= 14 && box2Pos.z <= 28 && box2Pos.x >= 100 && box2Pos.x <= 114)
	{
		if(!m_win)
			m_sound2->PlayWaveFile();
		m_win = true;

	}


	return;
}

bool ApplicationClass::RenderSceneToTexture()
{
	D3DXMATRIX worldMatrix, lightViewMatrix, lightProjectionMatrix, translateMatrix;
	float posX, posY, posZ;
	bool result;
	//Set the render to texture to be the rendering target.

		// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	// Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);


	// Generate the light view matrix based on the light's position.
	m_Light->GenerateViewMatrix();

	// Get the world matrix from the d3d object.
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// Get the view and orthographic matrices from the light object.
	m_Light->GetViewMatrix(lightViewMatrix);
	m_Light->GetProjectionMatrix(lightProjectionMatrix);

	// Setup the translation matrix for the cube model.
	m_pos1->GetPosition(posX, posY, posZ);
	D3DXMatrixTranslation(&worldMatrix, posX, posY, posZ);

	// Render the cube model with the depth shader.
	m_model->Render(m_Direct3D->GetDeviceContext());
	result = m_DepthShader->Render(m_Direct3D->GetDeviceContext(), m_model->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if (!result)
	{
		return false;
	}

	// Reset the world matrix.
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// Setup the translation matrix for the sphere model.
	m_pos2->GetPosition(posX, posY, posZ);
	D3DXMatrixTranslation(&worldMatrix, posX, posY, posZ);

	// Render the sphere model with the depth shader.
	m_model2->Render(m_Direct3D->GetDeviceContext());
	result = m_DepthShader->Render(m_Direct3D->GetDeviceContext(), m_model2->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if (!result)
	{
		return false;
	}

	// Reset the world matrix.
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// Setup the translation matrix for the ground model.
	//m_Position->GetPosition(posX, posY, posZ);
	posX = 0;
	posY = 0;
	posZ = 0;
	D3DXMatrixTranslation(&worldMatrix, posX, posY, posZ);

	// Render the ground model with the depth shader.
	m_Terrain->Render(m_Direct3D->GetDeviceContext());
	result = m_DepthShader->Render(m_Direct3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_Direct3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_Direct3D->ResetViewport();

	return true;
}

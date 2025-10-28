#include "CApp.h"
#include "Vector.h"

//Default constructor
CApp::CApp()
	: isRunning(true), pWindow(nullptr), pRenderer(nullptr)
{
}

bool CApp::OnInit()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return false;
	}

	//Create window
	pWindow = SDL_CreateWindow("RayTracer", 800, 600, SDL_WINDOW_RESIZABLE);
	
	if (pWindow == nullptr)
	{
		SDL_Log("Error while creating the window: %s", SDL_GetError());
		return false;
	}
	//Create renderer
	pRenderer = SDL_CreateRenderer(pWindow, nullptr);
	if (pRenderer == nullptr)
	{
		SDL_Log("No se pudo crear el renderer: %s", SDL_GetError());
		return false;
	}

	//Initialize the Image instance
	m_image.Initialize(1280, 720, pRenderer);

	//Test the camera class
	RT::Camera testCamera;
	testCamera.SetPosition(Vector<double>({ std::vector<double>{0.0, 0.0, 0.0} }));
	testCamera.SetLookAt(Vector<double>({ std::vector<double>{0.0, 2.0, 0.0} }));
	testCamera.SetUp(Vector<double>({ std::vector<double>{0.0, 0.0, 1.0} }));
	testCamera.SetLenght(1.0);
	testCamera.SetHorizontalSize(1.0);
	testCamera.setAspectRatio(1.0);
	testCamera.UpdateCameraGeometry();

	//Get the screen center and U, V vectors
	auto screenCenter = testCamera.GetScreenCenter();
	auto screenU = testCamera.GetU();
	auto screenV = testCamera.GetV();

	//And display to the terminal
	std::cout << "Camera screen center: " << std::endl;
	PrintVector(screenCenter);
	std::cout << "Camera screen U vector: " << std::endl;
	PrintVector(screenU);
	std::cout << "Camera screen V vector: " << std::endl;
	PrintVector(screenV);


	return true;
}

int CApp::OnExecute()
{
	if (OnInit() == false)
	{
		return -1;
	}

	SDL_Event Event;

	while (isRunning)
	{
		while (SDL_PollEvent(&Event))
		{
			OnEvent(&Event);
		}
		OnLoop();
		OnRender();
	}
	OnExit();
	return 0;
}

void CApp::OnEvent(SDL_Event* Event)
{
	switch (Event->type)
	{
	case SDL_EVENT_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void CApp::OnLoop()
{
	//Process
}

void CApp::OnRender()
{
	//Clear screen with a color
	SDL_SetRenderDrawColor(pRenderer, 255, 248, 231, 255);
	SDL_RenderClear(pRenderer);

	//Render the scene to the image
	m_scene.Render(m_image);

	//Display the image
	m_image.Display();

	//Present renderer
	SDL_RenderPresent(pRenderer);
}

void CApp::OnExit()
{
	//Destroy renderer
	if (pRenderer)
	{
		SDL_DestroyRenderer(pRenderer);
		pRenderer = nullptr;
	}
	//Destroy window
	if (pWindow)
	{
		SDL_DestroyWindow(pWindow);
		pWindow = nullptr;
	}
	//Quit SDL subsystems
	SDL_Quit();
}

//Private functions
void CApp::PrintVector(const Vector<double>& inputVector)
{
	int nRows = inputVector.GetNumDims();
	for (int row = 0; row < nRows; ++row)
	{
		std::cout << std::fixed << std::setprecision(6) << inputVector.GetElement(row) << std::endl;
	}
}









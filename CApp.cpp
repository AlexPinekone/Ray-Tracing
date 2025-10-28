#include "CApp.h"

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

	//Create colour variations
	for (int i = 0; i < 1280; ++i)
	{
		for (int j = 0; j < 720; ++j)
		{
			double red = static_cast<double>(i) / 1280.0;
			double green = static_cast<double>(j) / 720.0;
			double blue = 0.2;
			m_image.SetPixel(i, j, red, green, blue);
		}
	}

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









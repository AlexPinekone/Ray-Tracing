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









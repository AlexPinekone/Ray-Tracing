#pragma once
#include <SDL3/SDL.h>

class CApp
{
public:
	CApp();

	int OnExecute();
	bool OnInit();
	void OnEvent(SDL_Event* Event);
	void OnLoop();
	void OnRender();
	void OnExit();

private:
	//SDL2
	bool isRunning;
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;

};
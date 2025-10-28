#pragma once
#include <SDL3/SDL.h>
#include "Image.hpp"

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
	//An Instance of the Image class to store the image
	Image m_image;
	//SDL2
	bool isRunning;
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;

};
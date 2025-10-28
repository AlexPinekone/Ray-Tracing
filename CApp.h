#pragma once
#include <SDL3/SDL.h>
#include "Image.hpp"
#include "scene.hpp"
#include "camera.hpp"

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
	void PrintVector(const Vector<double>& inputVector);

private:
	//An Instance of the Image class to store the image
	Image m_image;

	//An instance of the Scene class to store the scene
	RT::Scene m_scene;

	//SDL2
	bool isRunning;
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;

};
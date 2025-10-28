#pragma once

#include <vector>
#include <SDL3/SDL.h>
#include "Image.hpp"

namespace RT 
{
	class Scene
	{
	public:
		Scene();

		//Funcion to perform the rendering of the scene
		bool Render(Image &outputImage);
	//private funcitions
	private:

	//private members
	private:

	};
}
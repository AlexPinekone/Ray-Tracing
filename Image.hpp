#pragma once

#include <string>
#include <vector>
#include <SDL3/SDL.h>

class Image
{
public:
	//The contructor
	Image();
	//Destructor
	~Image();

	//Initialize
	void Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer);

	//Function to set the colour of a pixel
	void SetPixel(const int x, const int y, const double red, const double green, const double blue);

	//Function to return the image for display
	void Display();

private:
	Uint32 ConvertColor(const double red, const double green, const double blue);

	void InitTexture();

private:
	//Array to store the image data
	std::vector<std::vector<double>> m_rChannel;
	std::vector<std::vector<double>> m_gChannel;
	std::vector<std::vector<double>> m_bChannel;

	//Store dimensions of the image
	int m_xSize, m_ySize;

	//SDL3 variables
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;

};
#include "Image.hpp"

//default constructor
Image::Image()
	: m_xSize(0), m_ySize(0), m_pRenderer(nullptr), m_pTexture(nullptr)
{
}

//Destructor
Image::~Image()
{
	if (m_pTexture)
	{
		SDL_DestroyTexture(m_pTexture);
	}
}

//Funcition to initialise the image
void Image::Initialize(const int xSize, const int ySize, SDL_Renderer* pRenderer)
{
	//Store Dimensions and the renderer pointer
	m_xSize = xSize;
	m_ySize = ySize;
	m_pRenderer = pRenderer;
	//Resize the colour channel arrays
	m_rChannel.resize(m_xSize, std::vector<double>(m_ySize, 0.0));
	m_gChannel.resize(m_xSize, std::vector<double>(m_ySize, 0.0));
	m_bChannel.resize(m_xSize, std::vector<double>(m_ySize, 0.0));
	//Initialise the texture
	InitTexture();
}

//Function to set the colour of a pixel
void Image::SetPixel(const int x, const int y, const double red, const double green, const double blue)
{
	m_rChannel[x][y] = red;
	m_gChannel[x][y] = green;
	m_bChannel[x][y] = blue;
}

//Function to return the dimensions of the image
int Image::GetXSize()
{
	return m_xSize;
}

int Image::GetYSize()
{
	return m_ySize;
}

//Function to generate the display
void Image::Display()
{
	//Allocate memory for pixel buffer
	Uint32* tempPixels = new Uint32[m_xSize * m_ySize];

	//Clear the pixels
	memset(tempPixels, 0, m_xSize * m_ySize * sizeof(Uint32));

	//Set the pixel colours
	for (int i=0; i < m_xSize; ++i)
	{
		for (int j = 0; j < m_ySize; ++j)
		{
			tempPixels[j * m_xSize + i] = ConvertColor(m_rChannel[i][j], m_gChannel[i][j], m_bChannel[i][j]);
		}
	}

	//Update the texture with the pixel buffer
	SDL_UpdateTexture(m_pTexture, nullptr, tempPixels, m_xSize * sizeof(Uint32));

	//Delete the pixel buffer
	delete[] tempPixels;

	//Copy the texture to the renderer
	SDL_FRect srcRect, bounds;
	srcRect.x = 0.0f;
	srcRect.y = 0.0f;
	srcRect.w = static_cast<float>(m_xSize);
	srcRect.h = static_cast<float>(m_ySize);
	bounds = srcRect;

	SDL_RenderTexture(m_pRenderer, m_pTexture, &srcRect, &bounds);
}

//Function to initialize the texture.
void Image::InitTexture()
{
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif
	//Delete any previously created texture
	if (m_pTexture != NULL)
		SDL_DestroyTexture(m_pTexture);

	//Create the texture that will store the image
	SDL_Surface* tempSurface = SDL_CreateSurface(m_xSize, m_ySize, SDL_PIXELFORMAT_ARGB8888);
	m_pTexture = SDL_CreateTexture(m_pRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, m_xSize, m_ySize);
	SDL_DestroySurface(tempSurface);
}

//Function to convert colours to Uint32
Uint32 Image::ConvertColor(const double red, const double green, const double blue)
{
	//Convert to unsigned integers
	Uint8 r = static_cast<Uint8>(SDL_clamp(red * 255.0, 0.0, 255.0));
	Uint8 g = static_cast<Uint8>(SDL_clamp(green * 255.0, 0.0, 255.0));
	Uint8 b = static_cast<Uint8>(SDL_clamp(blue * 255.0, 0.0, 255.0));

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	Uint32 pixelColor = (r << 24) | (g << 16) | (b << 8) | 255;
#else
	Uint32 pixelColor = (255 << 24) | (r << 16) | (g << 8) | b;
#endif
	return pixelColor;
}


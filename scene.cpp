#include "scene.hpp"

RT::Scene::Scene()
{

}

//Funcion to perform the rendering of the scene
bool RT::Scene::Render(Image& outputImage)
{
	//Get the dimensions of the output image
	int xSize = outputImage.GetXSize();
	int ySize = outputImage.GetYSize();

	//Create colour variations
	for (int i = 0; i < xSize; ++i)
	{
		for (int j = 0; j < ySize; ++j)
		{
			double red = (static_cast<double>(i) / static_cast<double>(xSize));
			double green = (static_cast<double>(j) / static_cast<double>(ySize));
			outputImage.SetPixel(i, j, red, green, 0.0);
		}
	}

	return true;
}
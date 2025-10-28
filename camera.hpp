#pragma once

#include "Vector.h"
#include "ray.hpp"

namespace RT
{
	class Camera
	{
	public:
		//Default constructor.
		Camera();	
		// Constructor with position, lookat point, up vector, field of view and aspect ratio.
		Camera(const Vector<double>& position, const Vector<double>& lookatPoint,
			const Vector<double>& upVector, const double fov, const double aspectRatio);
		// Function to generate a ray from the camera through a pixel.
		Ray GenerateRay(const double pixelX, const double pixelY) const;

		//Function to set the camera parameters.
		void SetPosition	(const Vector<double>& newPosition);
		void SetLookAt	(const Vector<double>& newLookAtPoint);
		void SetUp		(const Vector<double>& upVector);
		void SetLenght	(double newLenght);
		void SetHorizontalSize	(double newHorizontalSize);
		void setAspectRatio		(double newAspectRatio);

		//Fuctions to return camera parameters.
		Vector<double> GetPosition() const;
		Vector<double> GetLookAt() const;
		Vector<double> GetUp() const;
		Vector<double> GetU() const;
		Vector<double> GetV() const;
		Vector<double> GetScreenCenter() const;
		double GetLenght() const;
		double GetHorizontalSize() const;
		double GetAspectRatio() const;

		//Function to generate a ray
		Ray GenerateRay(float proyectionScreenX, int proyectionScreenY);

		//Function to update the camera geometry
		void UpdateCameraGeometry();

	private:
		Vector<double> m_cameraPosition{ 3 };
		Vector<double> m_cameraLookAt{ 3 };
		Vector<double> m_cameraUp{ 3 };
		double m_cameraLenght = 90.0;
		double m_cameraHorizontalSize = 1.0;
		double m_cameraAspectRatio = 0.0;

		Vector<double> m_alignmentVector{ 3 };
		Vector<double> m_projectionScreenU{ 3 };
		Vector<double> m_projectionScreenV{ 3 };
		Vector<double> m_projectionScreenCenter{ 3 };
	};
}
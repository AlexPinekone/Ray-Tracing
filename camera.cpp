#include "camera.hpp"
#include "ray.hpp"
#include <math.h>

RT::Camera::Camera(): 
	m_cameraPosition(Vector<double>{std::vector<double>{0.0, -10, 0.0}}),
	m_cameraLookAt(Vector<double>{std::vector<double>{0.0, 0.0, 0.0}}),
	m_cameraUp(Vector<double>{std::vector<double>{0.0, 0.0, 1.0}}),
	m_cameraLenght(1.0), 
	m_cameraHorizontalSize(1.0),
	m_cameraAspectRatio(1.0)
{
}

void RT::Camera::SetPosition(const Vector<double> &newPosition) {
	m_cameraPosition = newPosition;
}

void RT::Camera::SetLookAt(const Vector<double> &newLookAtPoint) {
	m_cameraLookAt = newLookAtPoint;
}

void RT::Camera::SetUp(const Vector<double> &upVector) {
	m_cameraUp = upVector;
}

void RT::Camera::SetLenght(double newLenght) {
	m_cameraLenght = newLenght;
}

void RT::Camera::SetHorizontalSize(double newHorizontalSize) {
	m_cameraHorizontalSize = newHorizontalSize;
}

void RT::Camera::setAspectRatio(double newAspectRatio) {
	m_cameraAspectRatio = newAspectRatio;
}

//Method to return the position of the camera
Vector<double> RT::Camera::GetPosition() const {
	return m_cameraPosition;
}

//Method to return the lookat point of the camera
Vector<double> RT::Camera::GetLookAt() const {
	return m_cameraLookAt;
}
//Method to return the up vector of the camera
Vector<double> RT::Camera::GetUp() const {
	return m_cameraUp;
}
//Method to return the lenght of the camera
double RT::Camera::GetLenght() const {
	return m_cameraLenght;
}
//Method to return the horizontal size of the camera
double RT::Camera::GetHorizontalSize() const {
	return m_cameraHorizontalSize;
}
//Method to return the aspect ratio of the camera
double RT::Camera::GetAspectRatio() const {
	return m_cameraAspectRatio;
}
//Method to return the U vector of the projection screen
Vector<double> RT::Camera::GetU() const {
	return m_projectionScreenU;
}
//Method to return the V vector of the projection screen
Vector<double> RT::Camera::GetV() const {
	return m_projectionScreenV;
}
//Method to return the center of the projection screen
Vector<double> RT::Camera::GetScreenCenter() const {
	return m_projectionScreenCenter;
}

//Function to update the camera geometry
void RT::Camera::UpdateCameraGeometry() {
	//Compute the alignment vector
	m_alignmentVector = (m_cameraLookAt - m_cameraPosition).Normalized();

	//Compute the projection screen U vector
	m_projectionScreenU = Vector<double>::cross(m_alignmentVector, m_cameraUp).Normalized();
	//Compute the projection screen V vector
	m_projectionScreenV = Vector<double>::cross(m_projectionScreenU, m_alignmentVector).Normalized();

	//Compute the projection screen center
	m_projectionScreenCenter = m_cameraPosition + (m_alignmentVector * m_cameraLenght);

	//Modify the U and V vectors according to the horizontal size and aspect ratio
	m_projectionScreenU = m_projectionScreenU * m_cameraHorizontalSize;
	m_projectionScreenV = m_projectionScreenV * (m_cameraHorizontalSize / m_cameraAspectRatio);
}

RT::Ray RT::Camera::GenerateRay(float proyectionScreenX, int proyectionScreenY) {
	//Compute the position on the projection screen
	Vector<double> proyectionScreenPoint = m_projectionScreenCenter +
		(m_projectionScreenU * (proyectionScreenX)) +
		(m_projectionScreenV * (proyectionScreenY));

	//Compute the ray direction
	//Vector<double> rayDirection = (proyectionScreenPoint - m_cameraPosition).Normalized();

	//Create and return the ray
	//RT::Ray generatedRay(m_cameraPosition, rayDirection);
	return RT::Ray(m_cameraPosition, proyectionScreenPoint);
}
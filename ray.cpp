#include "ray.hpp"

RT::Ray::Ray(const Vector<double>& origin, const Vector<double>& direction)
	: m_origin(origin), m_direction(direction), m_lab(m_origin - m_direction)
{
}

Vector<double> RT::Ray::GetOrigin() const
{
	return m_origin;
}

Vector<double> RT::Ray::GetDirection() const
{
	return m_direction;
}
#pragma once
#include "Vector.h"

namespace RT
{
	class Ray
	{
	public:
		// Constructor with origin and direction
		Ray(const Vector<double>& origin, const Vector<double>& direction);

		// Getters for origin and direction
		Vector<double> GetOrigin() const;
		Vector<double> GetDirection() const;
	private:
		Vector<double> m_origin{ 3 };
		Vector<double> m_direction{ 3 };
		Vector<double> m_lab{ 3 };
	};
}
#pragma once


namespace DXEngine
{
	class Colour
	{
	public:
		Colour() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}
		Colour(float red, float green, float blue, float alpha) : r(red), g(green), b(blue), a(alpha) {}

		// This function acts as an array
		// We call the first value, r, as it is the
		// first element in the array
		const float* ToArray() const { return &r; }

		// member vars
		float r, g, b, a;

	};
}
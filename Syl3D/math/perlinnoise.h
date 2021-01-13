#pragma once

namespace math
{
	class PerlinNoise
	{
	public:
		static float noise2D(float x, float y);

		static void setPersistence(float persis);

		static void setOctaves(unsigned int numOctaves);

		static float persistence();

		static unsigned int octaves();

	private:
		static float noise1(int x, int y);

		static float smoothNoise(float x, float y);

		static float interpolatedNoise(float x, float y);

		static float interpolate(float a, float b, float x);

	private:
		static float _persistence;
		static unsigned int _numOctaves;
	};
}
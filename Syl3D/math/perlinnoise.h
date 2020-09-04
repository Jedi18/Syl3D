#pragma once

namespace math
{
	class PerlinNoise
	{
	public:
		static float noise2D(float x, float y);

	private:
		static float noise1(int x, int y);

		static float smoothNoise(float x, float y);

		static float interpolatedNoise(float x, float y);

		static float interpolate(float a, float b, float x);

	private:
		static float persistence;
		static float numOctaves;
	};
}
#include "perlinnoise.h"
#include <cmath>

using namespace math;

float PerlinNoise::persistence = 0.5f;
unsigned int PerlinNoise::numOctaves = 8.0f;

float PerlinNoise::noise2D(float x, float y) {
    float total = 0;
    float p = persistence;
    unsigned int n = numOctaves - 1;

    for (int i = 0; i < n; i++) {
         float frequency = std::pow(2,i);
         float amplitude = std::pow(p,i);

         total = total + interpolatedNoise(x * frequency, y * frequency) * amplitude;
    }

    return total;
}

float PerlinNoise::noise1(int x, int y) {
    long long n = (long long)x + (long long)y * 57;
    n = (n << 13) ^ n;
    return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

float PerlinNoise::smoothNoise(float x, float y) {
    float corners = (noise1(x - 1, y - 1) + noise1(x + 1, y - 1) + noise1(x - 1, y + 1) + noise1(x + 1, y + 1)) / 16;
    float sides = (noise1(x - 1, y) + noise1(x + 1, y) + noise1(x, y - 1) + noise1(x, y + 1)) / 8;
    float center = noise1(x, y) / 4;
    return corners + sides + center;
}

float PerlinNoise::interpolatedNoise(float x, float y) {
    int integer_X = (int)x;
    float fractional_X = x - integer_X;

    int integer_Y = (int)y;
    float fractional_Y = y - integer_Y;

    float v1 = smoothNoise(integer_X, integer_Y);
    float v2 = smoothNoise(integer_X + 1, integer_Y);
    float v3 = smoothNoise(integer_X, integer_Y + 1);
    float v4 = smoothNoise(integer_X + 1, integer_Y + 1);

    float i1 = interpolate(v1, v2, fractional_X);
    float i2 = interpolate(v3, v4, fractional_X);

    return interpolate(i1, i2, fractional_Y);
}

float PerlinNoise::interpolate(float a, float b, float x) {
    float ft = x * 3.1415927;
    float f = (1 - std::cos(ft)) * .5;

    return  a * (1 - f) + b * f;
}

void PerlinNoise::setPersistence(float persis) {
    persistence = persis;
}

void PerlinNoise::setOctaves(unsigned int octaves) {
    numOctaves = octaves;
}
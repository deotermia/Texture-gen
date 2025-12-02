#include "perlin_noise.hpp"
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>

PerlinNoise::PerlinNoise (unsigned int seed)
  : seed_ (seed)
{
  init_permutation (seed);
}

void
PerlinNoise::init_permutation (unsigned int seed)
{
  /* Initialize with values 0..255.  */
  permutation_.resize (512);
  std::iota (permutation_.begin (), permutation_.begin () + 256, 0);

  /* Shuffle using seed.  */
  std::mt19937 engine (seed);
  std::shuffle (permutation_.begin (), permutation_.begin () + 256, engine);

  /* Duplicate for overflow prevention.  */
  for (int i = 0; i < 256; ++i)
    {
      permutation_[256 + i] = permutation_[i];
    }
}

float
PerlinNoise::fade (float t)
{
  /* 6t^5 - 15t^4 + 10t^3 */
  return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
}

float
PerlinNoise::lerp (float t, float a, float b)
{
  return a + t * (b - a);
}

float
PerlinNoise::grad (int hash, float x, float y, float z)
{
  /* Convert low 4 bits of hash code into 12 gradient directions.  */
  const int h = hash & 15;
  const float u = h < 8 ? x : y;
  const float v = h < 4 ? y : (h == 12 || h == 14 ? x : z);
  return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float
PerlinNoise::get_value (float x, float y) const
{
  return get_value (x, y, 0.0f);
}

float
PerlinNoise::get_value (float x, float y, float z) const
{
  /* Find unit cube that contains point.  */
  const int X = static_cast<int> (std::floor (x)) & 255;
  const int Y = static_cast<int> (std::floor (y)) & 255;
  const int Z = static_cast<int> (std::floor (z)) & 255;

  /* Find relative x, y, z of point in cube.  */
  x -= std::floor (x);
  y -= std::floor (y);
  z -= std::floor (z);

  /* Compute fade curves for x, y, z.  */
  const float u = fade (x);
  const float v = fade (y);
  const float w = fade (z);

  /* Hash coordinates of the 8 cube corners.  */
  const int A = permutation_[X] + Y;
  const int AA = permutation_[A] + Z;
  const int AB = permutation_[A + 1] + Z;
  const int B = permutation_[X + 1] + Y;
  const int BA = permutation_[B] + Z;
  const int BB = permutation_[B + 1] + Z;

  /* Add blended results from 8 corners of cube.  */
  const float res = lerp (w,
                          lerp (v,
                                lerp (u,
                                      grad (permutation_[AA], x, y, z),
                                      grad (permutation_[BA], x - 1, y, z)),
                                lerp (u,
                                      grad (permutation_[AB], x, y - 1, z),
                                      grad (permutation_[BB], x - 1, y - 1,
                                            z))),
                          lerp (v,
                                lerp (u,
                                      grad (permutation_[AA + 1], x, y, z - 1),
                                      grad (permutation_[BA + 1], x - 1, y,
                                            z - 1)),
                                lerp (u,
                                      grad (permutation_[AB + 1], x, y - 1,
                                            z - 1),
                                      grad (permutation_[BB + 1], x - 1,
                                            y - 1, z - 1))));

  /* Normalize to [-1, 1] range.  */
  return res;
}

void
PerlinNoise::set_seed (unsigned int seed)
{
  seed_ = seed;
  init_permutation (seed);
}

unsigned int
PerlinNoise::get_seed () const
{
  return seed_;
}
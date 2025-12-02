#include "simplex_noise.hpp"
#include <algorithm>
#include <numeric>
#include <random>
#include <cmath>

SimplexNoise::SimplexNoise (unsigned int seed)
  : seed_ (seed)
{
  init_permutation (seed);
}

void
SimplexNoise::init_permutation (unsigned int seed)
{
  permutation_.resize (512);
  std::iota (permutation_.begin (), permutation_.begin () + 256, 0);

  std::mt19937 engine (seed);
  std::shuffle (permutation_.begin (), permutation_.begin () + 256, engine);

  for (int i = 0; i < 256; ++i)
    {
      permutation_[256 + i] = permutation_[i];
    }
}

float
SimplexNoise::dot (const float g[2], float x, float y)
{
  return g[0] * x + g[1] * y;
}

float
SimplexNoise::get_value (float x, float y) const
{
  /* Skew the input space to determine which simplex cell we're in.  */
  const float s = (x + y) * F2;
  const int i = static_cast<int> (std::floor (x + s));
  const int j = static_cast<int> (std::floor (y + s));

  /* Unskew the cell origin back to (x,y) space.  */
  const float t = static_cast<float> (i + j) * G2;
  const float X0 = i - t;
  const float Y0 = j - t;
  const float x0 = x - X0;
  const float y0 = y - Y0;

  /* Determine which simplex we are in.  */
  int i1, j1;
  if (x0 > y0)
    {
      i1 = 1;
      j1 = 0;
    }
  else
    {
      i1 = 0;
      j1 = 1;
    }

  /* Offsets for middle corner in unskewed coordinates.  */
  const float x1 = x0 - i1 + G2;
  const float y1 = y0 - j1 + G2;
  const float x2 = x0 - 1.0f + 2.0f * G2;
  const float y2 = y0 - 1.0f + 2.0f * G2;

  /* Work out the hashed gradient indices of the three simplex corners.  */
  const int ii = i & 255;
  const int jj = j & 255;
  const int gi0 = permutation_[ii + permutation_[jj]] % 8;
  const int gi1 = permutation_[ii + i1 + permutation_[jj + j1]] % 8;
  const int gi2 = permutation_[ii + 1 + permutation_[jj + 1]] % 8;

  /* Calculate the contribution from the three corners.  */
  float n0, n1, n2;
  float t0 = 0.5f - x0 * x0 - y0 * y0;
  if (t0 < 0.0f)
    {
      n0 = 0.0f;
    }
  else
    {
      t0 *= t0;
      n0 = t0 * t0 * dot (GRAD2[gi0], x0, y0);
    }

  float t1 = 0.5f - x1 * x1 - y1 * y1;
  if (t1 < 0.0f)
    {
      n1 = 0.0f;
    }
  else
    {
      t1 *= t1;
      n1 = t1 * t1 * dot (GRAD2[gi1], x1, y1);
    }

  float t2 = 0.5f - x2 * x2 - y2 * y2;
  if (t2 < 0.0f)
    {
      n2 = 0.0f;
    }
  else
    {
      t2 *= t2;
      n2 = t2 * t2 * dot (GRAD2[gi2], x2, y2);
    }

  /* Return result scaled to [-1, 1] range.  */
  return 70.0f * (n0 + n1 + n2);
}

float
SimplexNoise::get_value (float x, float y, float z) const
{
  /* For MVP, return 2D noise for z=0.  */
  return get_value (x, y);
}

void
SimplexNoise::set_seed (unsigned int seed)
{
  seed_ = seed;
  init_permutation (seed);
}

unsigned int
SimplexNoise::get_seed () const
{
  return seed_;
}
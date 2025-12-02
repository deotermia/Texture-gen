#ifndef PERLIN_NOISE_HPP
#define PERLIN_NOISE_HPP

#include "noise_base.hpp"
#include <vector>

/* Implementation of Perlin noise algorithm.
   Based on original Ken Perlin's algorithm with improvements.  */
class PerlinNoise : public NoiseBase
{
public:
    /* Constructor with optional seed.  */
    explicit PerlinNoise (unsigned int seed = 1);

    /* Get 2D noise value.  */
    float get_value (float x, float y) const override;

    /* Get 3D noise value.  */
    float get_value (float x, float y, float z) const override;

    /* Set seed for noise generation.  */
    void set_seed (unsigned int seed) override;

    /* Get current seed.  */
    unsigned int get_seed () const override;

private:
    /* Permutation table for gradient indexing.  */
    std::vector<int> permutation_;

    /* Current seed value.  */
    unsigned int seed_;

    /* Initialize permutation table with given seed.  */
    void init_permutation (unsigned int seed);

    /* Fade function for smooth interpolation.  */
    static float fade (float t);

    /* Linear interpolation function.  */
    static float lerp (float t, float a, float b);

    /* Gradient function for dot product calculation.  */
    static float grad (int hash, float x, float y, float z);
};

#endif /* PERLIN_NOISE_HPP */
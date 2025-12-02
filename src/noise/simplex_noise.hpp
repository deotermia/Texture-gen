#ifndef SIMPLEX_NOISE_HPP
#define SIMPLEX_NOISE_HPP

#include "noise_base.hpp"
#include <vector>

/* Implementation of Simplex noise algorithm (by Ken Perlin).
   Improved version of Perlin noise with better computational
   complexity and fewer directional artifacts.  */
class SimplexNoise : public NoiseBase
{
public:
    /* Constructor with optional seed.  */
    explicit SimplexNoise (unsigned int seed = 1);

    /* Get 2D noise value.  */
    float get_value (float x, float y) const override;

    /* Get 3D noise value.  */
    float get_value (float x, float y, float z) const override;

    /* Set seed for noise generation.  */
    void set_seed (unsigned int seed) override;

    /* Get current seed.  */
    unsigned int get_seed () const override;

private:
    /* Permutation table.  */
    std::vector<int> permutation_;

    /* Gradients for 2D noise.  */
    static constexpr float GRAD2[8][2] = {
        {0, 1},   {1, 1},   {1, 0},   {1, -1},
        {0, -1},  {-1, -1}, {-1, 0},  {-1, 1}
    };

    /* Current seed value.  */
    unsigned int seed_;

    /* Skewing and unskewing factors for 2D.  */
    static constexpr float F2 = 0.366025403f;  /* (sqrt(3)-1)/2 */
    static constexpr float G2 = 0.211324865f;  /* (3-sqrt(3))/6 */

    /* Initialize permutation table.  */
    void init_permutation (unsigned int seed);

    /* Dot product for gradient calculation.  */
    static float dot (const float g[2], float x, float y);
};

#endif /* SIMPLEX_NOISE_HPP */
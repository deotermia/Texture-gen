#ifndef TEXTURE_PARAMS_HPP
#define TEXTURE_PARAMS_HPP

#include "../utils/color_gradient.hpp"

/* Enumeration of supported noise types.  */
enum class NoiseType
{
    PERLIN = 0,
    SIMPLEX = 1
  };

/* Structure holding all parameters for texture generation.  */
struct TextureParams
{
    /* Image dimensions.  */
    int width;
    int height;

    /* Noise parameters.  */
    NoiseType noise_type;
    unsigned int seed;
    float scale;           /* Noise scale factor.  */
    int octaves;           /* Number of octaves for fractal noise.  */
    float persistence;     /* Persistence factor for fractal noise.  */
    float lacunarity;      /* Lacunarity factor for fractal noise.  */
    float offset_x;        /* X offset for noise sampling.  */
    float offset_y;        /* Y offset for noise sampling.  */

    /* Color parameters.  */
    ColorGradient gradient; /* Color gradient for mapping noise values.  */

    /* Default constructor with sensible defaults.  */
    TextureParams ()
      : width (512),
        height (512),
        noise_type (NoiseType::SIMPLEX),
        seed (1),
        scale (5.0f),
        octaves (4),
        persistence (0.5f),
        lacunarity (2.0f),
        offset_x (0.0f),
        offset_y (0.0f)
    {
    }
};

#endif /* TEXTURE_PARAMS_HPP */
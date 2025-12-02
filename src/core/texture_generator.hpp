#ifndef TEXTURE_GENERATOR_HPP
#define TEXTURE_GENERATOR_HPP

#include <vector>
#include <memory>
#include "texture_params.hpp"
#include "../noise/noise_base.hpp"

/* Main texture generator class responsible for creating textures
   based on parameters and noise algorithms.  */
class TextureGenerator
{
public:
    /* Constructor taking texture parameters.  */
    explicit TextureGenerator (const TextureParams& params);

    /* Generate texture based on current parameters.  */
    std::vector<Color> generate () const;

    /* Update generator parameters.  */
    void set_params (const TextureParams& new_params);

    /* Get current parameters.  */
    TextureParams get_params () const;

private:
    /* Internal parameter storage.  */
    TextureParams params_;

    /* Noise algorithm instance.  */
    std::unique_ptr<NoiseBase> noise_algorithm_;

    /* Initialize noise algorithm based on parameters.  */
    void init_noise_algorithm ();

    /* Generate fractal (fBm) noise value at given coordinates.  */
    float generate_fractal_noise (float x, float y) const;

    /* Convert noise value to color using gradient.  */
    Color noise_to_color (float noise_value) const;
};

#endif /* TEXTURE_GENERATOR_HPP */
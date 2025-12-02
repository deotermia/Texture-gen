#include "texture_generator.hpp"
#include "../noise/noise_factory.hpp"
#include <stdexcept>
#include <cmath>

TextureGenerator::TextureGenerator (const TextureParams& params)
  : params_ (params)
{
  init_noise_algorithm ();
}

void
TextureGenerator::init_noise_algorithm ()
{
  noise_algorithm_ = NoiseFactory::create_noise (params_.noise_type);
  noise_algorithm_->set_seed (params_.seed);
}

std::vector<Color>
TextureGenerator::generate () const
{
  if (!noise_algorithm_)
    {
      throw std::runtime_error ("Noise algorithm not initialized");
    }

  std::vector<Color> pixels;
  pixels.reserve (params_.width * params_.height);

  for (int y = 0; y < params_.height; ++y)
    {
      for (int x = 0; x < params_.width; ++x)
        {
          /* Normalize coordinates and apply scale.  */
          const float nx = (static_cast<float> (x) / params_.width)
                           * params_.scale + params_.offset_x;
          const float ny = (static_cast<float> (y) / params_.height)
                           * params_.scale + params_.offset_y;

          /* Generate fractal noise value.  */
          const float noise_value = generate_fractal_noise (nx, ny);

          /* Convert noise value to color.  */
          const Color pixel_color = noise_to_color (noise_value);

          pixels.push_back (pixel_color);
        }
    }

  return pixels;
}

float
TextureGenerator::generate_fractal_noise (float x, float y) const
{
  float value = 0.0f;
  float amplitude = 1.0f;
  float frequency = 1.0f;
  float max_value = 0.0f;

  for (int i = 0; i < params_.octaves; ++i)
    {
      const float sample_x = x * frequency;
      const float sample_y = y * frequency;

      /* Get noise value from algorithm.  */
      float noise_val = noise_algorithm_->get_value (sample_x, sample_y);

      /* Map from [-1, 1] to [0, 1].  */
      noise_val = (noise_val + 1.0f) * 0.5f;

      value += noise_val * amplitude;

      max_value += amplitude;

      amplitude *= params_.persistence;
      frequency *= params_.lacunarity;
    }

  /* Normalize to [0, 1] range.  */
  if (max_value > 0.0f)
    {
      value /= max_value;
    }

  return value;
}

Color
TextureGenerator::noise_to_color (float noise_value) const
{
  /* Clamp noise value to [0, 1] range.  */
  const float clamped_value = std::max (0.0f, std::min (1.0f, noise_value));

  /* Get color from gradient.  */
  return params_.gradient.get_color (clamped_value);
}

void
TextureGenerator::set_params (const TextureParams& new_params)
{
  params_ = new_params;
  init_noise_algorithm ();
}

TextureParams
TextureGenerator::get_params () const
{
  return params_;
}
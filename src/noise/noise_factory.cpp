#include "noise_factory.hpp"
#include "perlin_noise.hpp"
#include "simplex_noise.hpp"
#include <stdexcept>

std::unique_ptr<NoiseBase>
NoiseFactory::create_noise (NoiseType type)
{
    return create_noise (type, 1);
}

std::unique_ptr<NoiseBase>
NoiseFactory::create_noise (NoiseType type, unsigned int seed)
{
    switch (type)
    {
        case NoiseType::PERLIN:
            return std::make_unique<PerlinNoise> (seed);
        case NoiseType::SIMPLEX:
            return std::make_unique<SimplexNoise> (seed);
        default:
            throw std::invalid_argument ("Unknown noise type");
    }
}
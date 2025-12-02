#ifndef NOISE_FACTORY_HPP
#define NOISE_FACTORY_HPP

#include "noise_base.hpp"
#include "../core/texture_params.hpp"
#include <memory>

/* Factory class for creating noise algorithm instances.
   Implements Factory Method pattern for noise creation.  */
class NoiseFactory
{
public:
    /* Create noise algorithm based on type.  */
    static std::unique_ptr<NoiseBase> create_noise (NoiseType type);

    /* Create noise algorithm with specific seed.  */
    static std::unique_ptr<NoiseBase> create_noise (NoiseType type,
                                                    unsigned int seed);
};

#endif /* NOISE_FACTORY_HPP */
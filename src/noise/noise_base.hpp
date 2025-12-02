#ifndef NOISE_BASE_HPP
#define NOISE_BASE_HPP

/* Abstract base class for noise algorithms.
   Defines interface that all noise implementations must follow.  */
class NoiseBase
{
public:
    virtual ~NoiseBase () = default;

    /* Get noise value at 2D coordinates.  */
    virtual float get_value (float x, float y) const = 0;

    /* Get noise value at 3D coordinates.  */
    virtual float get_value (float x, float y, float z) const = 0;

    /* Set seed for noise generation.  */
    virtual void set_seed (unsigned int seed) = 0;

    /* Get current seed.  */
    virtual unsigned int get_seed () const = 0;
};

#endif /* NOISE_BASE_HPP */
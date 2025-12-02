#ifndef COLOR_GRADIENT_HPP
#define COLOR_GRADIENT_HPP

#include <vector>
#include <utility>
#include <algorithm>
#include "color.hpp"

/* Color stop for gradient definition.  */
struct ColorStop
{
    float position;  /* Position in [0.0, 1.0] range.  */
    Color color;     /* Color at this position.  */

    ColorStop (float pos, const Color& col)
      : position (pos),
        color (col)
    {
    }

    /* For sorting by position.  */
    bool operator< (const ColorStop& other) const
    {
        return position < other.position;
    }
};

/* Class for defining and evaluating color gradients.
   Supports multiple color stops with linear interpolation.  */
class ColorGradient
{
public:
    ColorGradient ();

    /* Add a color stop at specified position.  */
    void add_color_stop (float position, const Color& color);

    /* Get color at specified position in gradient.  */
    Color get_color (float position) const;

    /* Clear all color stops.  */
    void clear ();

    /* Get number of color stops.  */
    size_t size () const;

private:
    /* Vector of color stops, always sorted by position.  */
    std::vector<ColorStop> stops_;

    /* Ensure stops are sorted after modification.  */
    void sort_stops ();
};

#endif /* COLOR_GRADIENT_HPP */
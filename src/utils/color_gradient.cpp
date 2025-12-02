#include "color_gradient.hpp"
#include <stdexcept>
#include <cmath>

ColorGradient::ColorGradient ()
{
  /* Default gradient: black to white.  */
  add_color_stop (0.0f, Color (0, 0, 0));
  add_color_stop (1.0f, Color (255, 255, 255));
}

void
ColorGradient::add_color_stop (float position, const Color& color)
{
  if (position < 0.0f || position > 1.0f)
    {
      throw std::out_of_range ("Gradient position must be in [0.0, 1.0] range");
    }

  stops_.emplace_back (position, color);
  sort_stops ();
}

Color
ColorGradient::get_color (float position) const
{
  if (stops_.empty ())
    {
      return Color (); /* Return black if no stops defined.  */
    }

  /* Clamp position to [0.0, 1.0].  */
  position = std::max (0.0f, std::min (1.0f, position));

  /* Handle edge cases.  */
  if (position <= stops_.front ().position)
    {
      return stops_.front ().color;
    }
  if (position >= stops_.back ().position)
    {
      return stops_.back ().color;
    }

  /* Find the two stops between which position lies.  */
  for (size_t i = 0; i < stops_.size () - 1; ++i)
    {
      if (position >= stops_[i].position && position <= stops_[i + 1].position)
        {
          const float t = (position - stops_[i].position)
                          / (stops_[i + 1].position - stops_[i].position);

          /* Linear interpolation between colors.  */
          const Color& c1 = stops_[i].color;
          const Color& c2 = stops_[i + 1].color;

          const unsigned char r = static_cast<unsigned char> (
              c1.r + t * (c2.r - c1.r));
          const unsigned char g = static_cast<unsigned char> (
              c1.g + t * (c2.g - c1.g));
          const unsigned char b = static_cast<unsigned char> (
              c1.b + t * (c2.b - c1.b));
          const unsigned char a = static_cast<unsigned char> (
              c1.a + t * (c2.a - c1.a));

          return Color (r, g, b, a);
        }
    }

  /* Should never reach here.  */
  return Color ();
}

void
ColorGradient::clear ()
{
  stops_.clear ();
}

size_t
ColorGradient::size () const
{
  return stops_.size ();
}

void
ColorGradient::sort_stops ()
{
  std::sort (stops_.begin (), stops_.end ());
}
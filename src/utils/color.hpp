#ifndef COLOR_HPP
#define COLOR_HPP

/* Simple RGBA color structure with 8-bit channels.  */
struct Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    /* Default constructor (black, opaque).  */
    Color ()
      : r (0),
        g (0),
        b (0),
        a (255)
    {
    }

    /* Constructor with unsigned char values.  */
    Color (unsigned char red, unsigned char green, unsigned char blue,
           unsigned char alpha = 255)
      : r (red),
        g (green),
        b (blue),
        a (alpha)
    {
    }

    /* Constructor with int values (common case).  */
    Color (int red, int green, int blue, int alpha = 255)
      : r (static_cast<unsigned char> (red)),
        g (static_cast<unsigned char> (green)),
        b (static_cast<unsigned char> (blue)),
        a (static_cast<unsigned char> (alpha))
    {
    }

    /* Constructor from float values [0.0, 1.0].  */
    Color (float red, float green, float blue, float alpha = 1.0f)
      : r (static_cast<unsigned char> (red * 255.0f)),
        g (static_cast<unsigned char> (green * 255.0f)),
        b (static_cast<unsigned char> (blue * 255.0f)),
        a (static_cast<unsigned char> (alpha * 255.0f))
    {
    }

    /* Check if two colors are equal.  */
    bool operator== (const Color& other) const
    {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }

    /* Check if two colors are not equal.  */
    bool operator!= (const Color& other) const
    {
        return !(*this == other);
    }
};

#endif /* COLOR_HPP */
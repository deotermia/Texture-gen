#ifndef IMAGE_WRITER_HPP
#define IMAGE_WRITER_HPP

#include <string>
#include <vector>
#include "color.hpp"

class ImageWriter
{
public:
    /* Write pixel data to PPM file (simple ASCII format).  */
    static bool write_to_ppm (const std::string& filename,
                              const std::vector<Color>& pixels,
                              int width, int height);

    /* Alias for compatibility.  */
    static bool write_to_png (const std::string& filename,
                              const std::vector<Color>& pixels,
                              int width, int height)
    {
        return write_to_ppm (filename, pixels, width, height);
    }

    static bool write_to_bmp (const std::string& filename,
                              const std::vector<Color>& pixels,
                              int width, int height)
    {
        return write_to_ppm (filename, pixels, width, height);
    }
};

#endif /* IMAGE_WRITER_HPP */
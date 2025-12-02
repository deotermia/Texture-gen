#include "image_writer.hpp"
#include <fstream>
#include <vector>
#include <stdexcept>

bool
ImageWriter::write_to_ppm (const std::string& filename,
                           const std::vector<Color>& pixels,
                           int width, int height)
{
  if (static_cast<size_t> (width * height) != pixels.size ())
  {
    throw std::invalid_argument (
        "Pixel count doesn't match image dimensions");
  }

  std::ofstream file (filename);
  if (!file.is_open ())
  {
    return false;
  }

  /* Write PPM header (P3 = ASCII RGB).  */
  file << "P3\n";
  file << width << " " << height << "\n";
  file << "255\n";  /* Max color value.  */

  /* Write pixel data.  */
  const int max_pixels_per_line = 5;
  int pixel_count = 0;

  for (int i = 0; i < width * height; ++i)
  {
    const Color& pixel = pixels[i];
    file << static_cast<int> (pixel.r) << " "
         << static_cast<int> (pixel.g) << " "
         << static_cast<int> (pixel.b);

    pixel_count++;
    if (pixel_count >= max_pixels_per_line)
    {
      file << "\n";
      pixel_count = 0;
    }
    else if (i < width * height - 1)
    {
      file << " ";
    }
  }

  if (pixel_count > 0)
  {
    file << "\n";
  }

  file.close ();
  return true;
}
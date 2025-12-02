/* Main entry point for texture generator application.  */

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>

#include "core/texture_generator.hpp"
#include "core/texture_params.hpp"
#include "utils/image_writer.hpp"
#include "noise/noise_factory.hpp"

/* Auto-open image after generation (Windows).  */
#ifdef _WIN32
#include <cstdlib>
#endif

int
main (int argc, char *argv[])
{
    /* Set default parameters.  */
    int width = 512;
    int height = 512;
    std::string output_file = "texture.ppm";
    NoiseType noise_type = NoiseType::SIMPLEX;
    unsigned int seed = static_cast<unsigned int> (std::time (nullptr));

    /* Parse command line arguments if provided.  */
    if (argc >= 4)
    {
        width = std::stoi (argv[1]);
        height = std::stoi (argv[2]);
        output_file = argv[3];

        if (argc > 4)
        {
            int type_val = std::stoi (argv[4]);
            noise_type = static_cast<NoiseType> (type_val);
        }

        if (argc > 5)
        {
            seed = static_cast<unsigned int> (std::stoul (argv[5]));
        }
    }
    else
    {
        std::cout << "Using default parameters:\n";
        std::cout << "  Size: " << width << "x" << height << "\n";
        std::cout << "  Output: " << output_file << "\n";
        std::cout << "  Noise: " << (noise_type == NoiseType::PERLIN ? "Perlin" : "Simplex") << "\n";
        std::cout << "  Seed: " << seed << "\n";
        std::cout << "\nUsage: " << (argc > 0 ? argv[0] : "texture_gen")
                  << " <width> <height> <output.ppm> [noise_type] [seed]\n";
        std::cout << "Noise types: 0=Perlin, 1=Simplex (default)\n\n";
    }

    std::cout << "Generating texture " << width << "x" << height
              << " with seed=" << seed
              << " and noise type=" << static_cast<int> (noise_type) << "\n";

    try
    {
        /* Create texture parameters.  */
        TextureParams params;
        params.width = width;
        params.height = height;
        params.seed = seed;
        params.noise_type = noise_type;
        params.scale = 5.0f;
        params.octaves = 4;
        params.persistence = 0.5f;
        params.lacunarity = 2.0f;
        params.offset_x = 0.0f;
        params.offset_y = 0.0f;

        /* Create color gradient for texture coloring.  */
        ColorGradient gradient;
        gradient.add_color_stop (0.0f, Color (0, 0, 100));     /* Dark blue */
        gradient.add_color_stop (0.3f, Color (240, 240, 64));  /* Sandy */
        gradient.add_color_stop (0.6f, Color (34, 139, 34));   /* Green */
        gradient.add_color_stop (0.8f, Color (139, 69, 19));   /* Brown */
        gradient.add_color_stop (1.0f, Color (255, 255, 255)); /* White */

        params.gradient = gradient;

        /* Create and configure texture generator.  */
        TextureGenerator generator (params);

        /* Generate texture.  */
        std::vector<Color> pixels = generator.generate ();

        /* Save to PPM file.  */
        if (ImageWriter::write_to_ppm (output_file, pixels, width, height))
        {
            std::cout << "Texture saved to: " << output_file << "\n";

            /* Auto-open in Windows.  */
            #ifdef _WIN32
            std::string open_cmd = "start \"\" \"" + output_file + "\"";
            std::system (open_cmd.c_str ());
            std::cout << "Opening image...\n";
            #endif
        }
        else
        {
            std::cerr << "Error saving file!\n";
            return EXIT_FAILURE;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what () << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
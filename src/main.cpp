#include <iostream>
#include <fstream>
#include <filesystem>
#include <cassert>
#include <cstdint>
#include <lodepng/lodepng.h>

#define ERROR(str) { std::cout << "[ERROR] " << str; return -1; }

static struct
{
    std::filesystem::path input_path;
    std::filesystem::path output_path;
    float block_size;
    uint32_t ss;
    bool invert;

    std::vector<uint8_t> bitmap;
    uint32_t bitmap_w;
    uint32_t bitmap_h;
} settings;

// calculates the average luma in the pixel block starting at x, y
static inline double block_luma(uint32_t x, uint32_t y)
{
    static const float sample_frac = settings.block_size / settings.ss;
    uint64_t luma_sum = 0;
    uint32_t pixels_sampled = 0;

    for (uint32_t dy = 0; dy < settings.ss; dy++)
    {
        for (uint32_t dx = 0; dx < settings.ss; dx++)
        {
            const uint32_t sample_x = x + sample_frac * dx;
            const uint32_t sample_y = y + sample_frac * dy;

            if (sample_x > settings.bitmap_w || sample_y > settings.bitmap_h)
                continue;

            const uint64_t index = (sample_y * settings.bitmap_w + sample_x) * 4;

            const uint8_t r = settings.bitmap[index + 0];
            const uint8_t g = settings.bitmap[index + 1];
            const uint8_t b = settings.bitmap[index + 2];
            const uint8_t a = settings.bitmap[index + 3];

            // luma from color values from: https://stackoverflow.com/questions/596216/formula-to-determine-brightness-of-rgb-color
            // added alpha channel logic for always displaying whitespace when alpha == 0

            if (a == 0)
                luma_sum += !settings.invert * 255;
            else
                luma_sum += 0.299f * r + 0.587f * g + 0.114f * b;
            pixels_sampled++;
        }
    }
    // get average of all pixels sampled and remap it to 0-1
    return luma_sum / (pixels_sampled * 255.0);
}

int main()
{
    std::string pixel_chars = "@%#+?*;=-:.` ";

    // get settings from terminal

    std::cout << "[input file] [output file] [downsampling] [supersampling] [invert]" << "\n> ";
    std::cin >> settings.input_path >> settings.output_path >> settings.block_size >> settings.ss >> settings.invert;
    
    if (!settings.ss)
        ERROR("the smallest value for supersampling is 1 (disabled)");

    settings.ss = std::min((float)settings.ss, settings.block_size);

    if (settings.invert)
        std::reverse(pixel_chars.begin(), pixel_chars.end());

    // load png bitmap from file
    
    if (lodepng::decode(settings.bitmap, settings.bitmap_w, settings.bitmap_h, settings.input_path.string()) != 0)
        ERROR("couldn't load file");

    std::ofstream output(settings.output_path);

    // calculate ascii characters for each block in image and write it to output

    for (float y = 0; y < settings.bitmap_h - settings.block_size; y += settings.block_size)
    {
        for (float x = 0; x < settings.bitmap_w - settings.block_size; x += settings.block_size)
        {
            // calculate the block luma
            const double luma = block_luma(x, y);

            // get character from block luminosity
            const uint32_t char_index = luma * (pixel_chars.length() - 1);

            // add two chars per "pixel" since chars typically have a 2:1 size ratio
            output << std::string(2, pixel_chars[char_index]);
        }
        output << '\n';
    }
    std::cout << "Image saved as " << settings.output_path;
}

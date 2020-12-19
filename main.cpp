#include <iostream>
#include <fstream>
#include "lodepng.h"

#define ERROR(str) (std::cout << "[ERROR] " << str); return -1;

typedef unsigned char uchar;
typedef unsigned int  uint;
typedef unsigned int  ulong;

constexpr std::string_view PIXEL_CHARS = " `.:-=;*?+#%@@";

int main(int argc, char* argv[])
{
	std::string filename;
	std::string output;
	uint block_size;
	uint ss;

	if (argc >= 5)
	{
		filename   = std::string(argv[1]);
		output     = std::string(argv[2]);
		block_size = std::stoi(argv[3]);
		ss         = std::stoi(argv[4]);
	}
	else
	{
		std::cout << "[input file] [output file] [downsampling] [supersampling]" << std::endl << "> ";
		std::cin >> filename >> output >> block_size >> ss;
	}

	std::cout << std::endl;

	if (!ss)
	{
		ERROR("the smallest value for supersampling is 1 (disabled)");
	}

	ss = std::min(ss, block_size);

	// load png bitmap from file

	std::vector<uchar> bitmap;
	uint width, height;

	if (lodepng::decode(bitmap, width, height, filename) > 0)
	{
		ERROR("couldn't load file");
	}

	// generate ascii from pixel luminosity values

	std::string buf;
	buf.reserve(2 * ((width * height) / (block_size * block_size)));

	for (uint y = 0; y < height; y += block_size)
	{
		for (uint x = 0; x < width; x += block_size)
		{
			uint block_lum = 0;
			uint sampled = 0;

			// supersampling

			for (uint dy = 0; dy < ss; dy++)
			{
				for (uint dx = 0; dx < ss; dx++)
				{
					static const float sample_frac = block_size / ss;

					uint sample_x = x + sample_frac * dx;
					uint sample_y = y + sample_frac * dy;

					if (sample_x > width || sample_y > height)
						continue;

					const ulong index = (sample_y * width + sample_x) * 4;

					const uchar r = bitmap[index + 0];
					const uchar g = bitmap[index + 1];
					const uchar b = bitmap[index + 2];
					const uchar a = bitmap[index + 3];

					// https://stackoverflow.com/questions/596216/formula-to-determine-brightness-of-rgb-color
					// with added alpha channel
					block_lum += a * (r + r + b + g + g + g) / (6 * 255);
					sampled++;
				}
			}

			// shouldn't ever be an issue but just in case
			if (!sampled)
				continue;

			// divide to get average luminosities of pixels sampled in block
			block_lum /= sampled;

			// get character from block luminosity
			const uint char_index = (block_lum / 255.f) * (PIXEL_CHARS.length() - 1);

			// add two chars per "pixel" since chars typically have a 2:1 size ratio
			buf += std::string(2, PIXEL_CHARS[char_index]);
		}
		buf += '\n';
	}

	// write to output
	std::ofstream stream(output);
	stream << buf;
	stream.close();

	std::cout << "Image saved as " << output;
}

#include <ostream>

#include "ppm.h"

void PPMWriter::write(std::ostream &output, const Image &image) {
	output << "P3\n"
		   << image.width() << ' ' << image.height() << '\n'
		   << "255\n";

	for (size_t i = 0; i < image.height(); i++) {
		for (size_t j = 0; j < image.width(); j++) {
			const Pixel &px = image(i, j);
			output << std::to_string(px.r) << ' ' << std::to_string(px.g) << ' '
				   << std::to_string(px.b) << ' ';
		}
		output << '\n';
	}
}

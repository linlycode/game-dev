#ifndef PPM_H
#define PPM_H

#include "image.h"

class PPMWriter : public ImageWriter {
public:
	std::string extension() const { return ".ppm"; }

	void write(std::ostream &output, const Image &image);
};

#endif

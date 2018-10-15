#include <fstream>

#include "image.h"

void ImageWriter::write(const std::string &filepath, const Image &image) {
	std::string path(filepath);

	// append extension if filepath doesn't contain extension
	size_t pos = filepath.find('.');
	if (pos == std::string::npos || pos == 0) {
		path = filepath + this->extension();
	}

	std::fstream file(path, std::ios::binary | std::ios::out);
	write(file, image);
}

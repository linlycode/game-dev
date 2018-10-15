#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include <string>
#include <vector>

struct Pixel {
	uint8_t r, g, b;

	Pixel() : r(0), g(0), b(0) {}

	Pixel(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
};

class Image {
private:
	size_t m_width, m_height;
	std::vector<Pixel> m_data;

public:
	Image(size_t width, size_t height)
		: m_width(width), m_height(height), m_data(m_width * m_height) {}

	size_t width() const { return m_width; }
	size_t height() const { return m_height; }

	const Pixel &operator()(size_t i, size_t j) const {
		return m_data[i * m_width + j];
	}

	Pixel &operator()(size_t i, size_t j) { return m_data[i * m_width + j]; }
};

class ImageWriter {
public:
	virtual ~ImageWriter() {}

	virtual std::string extension() const { return ""; }

	virtual void write(std::ostream &output, const Image &image) = 0;
	void write(const std::string &filepath, const Image &image);
};

#endif

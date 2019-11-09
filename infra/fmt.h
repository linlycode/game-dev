#ifndef FMT_H
#define FMT_H

#include <string>
#include <iostream>

namespace fmt {

	std::string sprintf(const char *format, ...);

	// fprintf converts arguments to string in given format and writes the
	// string to the stream, returns number of characters written if successful
	int fprintf(std::ostream &stream, const char *format, ...);

} // namespace fmt

#endif

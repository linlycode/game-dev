#include <cstdarg>

#include "fmt.h"

namespace {
	std::string format_string(const char *format, va_list args) {
		va_list cp;
		va_copy(cp, args);

		char buf[1024];

		int n = vsnprintf(buf, sizeof(buf), format, args);
		va_end(args);

		if (static_cast<size_t>(n) >= sizeof(buf)) {
			std::string str(n + 1, '\0');

			vsnprintf(&str[0], n + 1, format, cp);
			va_end(cp);

			str.resize(n);
			return str;
		}

		va_end(cp);

		if (n < 0) {
			throw std::runtime_error("error occurred while formatting string");
		}
		return buf;
	}
} // namespace

namespace fmt {

	std::string sprintf(const char *format, ...) {
		va_list args;

		va_start(args, format);
		std::string str = format_string(format, args);

		return str;
	}

	int fprintf(std::ostream &stream, const char *format, ...) {
		va_list args;

		va_start(args, format);
		std::string str = format_string(format, args);

		stream << str;
		return str.size();
	}

} // namespace fmt

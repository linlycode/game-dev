#include "filepath.h"

#ifdef _WIN32
#define SEP '\\'
#else
#define SEP '/'
#endif

static char get_separator(const std::string &s) {
	if (s.find('/') != std::string::npos) {
		return '/';
	} else if (s.find('\\') != std::string::npos) {
		return '\\';
	} else {
		return SEP;
	}
}

namespace filepath {

	std::string join(const std::string &base, const std::string &name) {
		char sep = get_separator(base);
		return base.back() == sep ? base + name : base + sep + name;
	}

} // namespace filepath

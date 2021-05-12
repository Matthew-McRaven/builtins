#include "helper.hpp"
std::string as_string(const unsigned char* start, size_t len) {
	return std::string(reinterpret_cast< const char* >(start), len);
}


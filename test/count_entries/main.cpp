#include "helper.hpp"

int main() {
	auto fig = registry::instance().find("pep10", 5, 3);
	if(!fig) return 1;
	else return 0;
}
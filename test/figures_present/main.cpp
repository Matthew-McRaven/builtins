#include "ex_registry.hpp"

int main() {
	auto fig = registry::instance().find("pep10", 5, "03");
	if(!fig) return 1;
	else return 0;
}
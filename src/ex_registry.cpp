#include "ex_registry.hpp"
#include <iostream>

registry* registry::_instance = nullptr;


std::string as_string(const unsigned char* start, size_t len) {
	return std::string(reinterpret_cast< const char* >(start), len);
}

// Test
test::test(std::string output): output(output)
{

}

test::test(std::string output, std::string input): output(output), input(input)
{

}

// Figure
figure::figure(std::string proc, uint16_t chapter, std::string fig, std::vector<test> tests, std::map<element_type, std::string> elements):
	proc(proc), chapter(chapter), fig(fig), tests(tests), elements(elements)
{

}

// Macro
macro::macro(std::string name, std::string text): name(name), text(text) {}

// Registry
void registry::add_figure(figure figure)
{
	//std::cout << figure.proc << " " << figure.chapter << "." << figure.fig_num << std::endl;
	_figures.emplace_back(figure);
}


std::optional<figure> registry::find(std::string proc, uint16_t chapter, std::string figure) const
{
	auto match = [=](const struct figure& fig){ return fig.proc==proc && fig.chapter==chapter && fig.fig==figure;};
	if(auto val = std::find_if(_figures.begin(), _figures.end(), match); val!=_figures.end()) return *val;
	else return std::nullopt;
	
}

const std::vector<figure>& registry::figures() const
{
	return _figures;
}

void registry::add_macro(macro macro)
{
	_macros.emplace_back(macro);
}

std::optional<macro> registry::find(std::string macro_name) const
{
	auto match = [=](const macro& mac){ return mac.name == macro_name;};
	if(auto val = std::find_if(_macros.begin(), _macros.end(), match); val!=_macros.end()) return *val;
	else return std::nullopt;
	
}

const std::vector<macro>& registry::macros() const
{
	return _macros;
}

registry& registry::instance() {
	if(_instance == nullptr) _instance = new registry();
	return *_instance;
}
registry::registry(): _figures()
{

}
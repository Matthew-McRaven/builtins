#include "helper.hpp"
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
figure::figure(std::string proc, uint16_t chapter, uint16_t fig_num, std::vector<test> tests, std::map<element_type, std::string> elements):
	proc(proc), chapter(chapter), fig_num(fig_num), tests(tests), elements(elements)
{

}

// Registry
void registry::add_figure(figure figure)
{
	//std::cout << figure.proc << " " << figure.chapter << "." << figure.fig_num << std::endl;
	_figures.emplace_back(figure);
}

std::optional<figure> registry::find(std::string proc, uint16_t chapter, uint16_t fig_num) const
{
	auto match = [=](const figure& fig){ return fig.proc==proc && fig.chapter==chapter && fig.fig_num==fig_num;};
	if(auto val = std::find_if(_figures.begin(), _figures.end(), match); val!=_figures.end()) return *val;
	else return std::nullopt;
	
}
const std::vector<figure>& registry::figures() const
{
	return _figures;
}
registry& registry::instance() {
	if(_instance == nullptr) _instance = new registry();
	return *_instance;
}
registry::registry(): _figures()
{

}
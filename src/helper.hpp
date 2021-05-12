#pragma once

#include <map>
#include <optional>
#include <stdint.h>
#include <string>
#include <vector>

#define catx(A, B) A ## B
#define cat(A, B) catx(A, B)

#define stx(A) #A
#define st(A) stx(A)

std::string as_string(const unsigned char* start, size_t len);

enum class element_type
{
	kC, // For C source
	kPep, kPepl, // For Pep assembly code and listings
	kPepo, kPeph, kPepb, // For Pep object code
	kPepm // For Pep macros.
	// Note, microcode programs not yet supported
};

struct test
{
	test(std::string output);
	test(std::string input, std::string output);

	std::optional<std::string> input;
	std::string output;
};

struct figure
{
	figure(std::string proc, uint16_t chapter, uint16_t fig_num, std::vector<test> tests, std::map<element_type, std::string> elements);
	uint16_t chapter, fig_num;
	std::vector<test> tests;
};

class registry
{
public:
	static registry& instance();
	void add_figure(figure fig);
	std::optional<figure> find(std::string proc, uint16_t chapter, uint16_t figure) const;
private:
	static registry* _instance;
	registry();
	std::vector<figure> _figures;
};
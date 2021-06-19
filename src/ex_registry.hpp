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
	test(std::string output, std::string input);

	std::optional<std::string> input;
	std::string output;
};

struct figure
{
	figure(std::string proc, uint16_t chapter, std::string fig, std::vector<test> tests, std::map<element_type, std::string> elements);
	const std::string proc;
	const uint16_t chapter;
	// Must not be named the same as the class.
	std::string fig;
	const std::vector<test> tests;
	const std::map<element_type, std::string> elements;
};

struct macro
{
	macro(std::string name, std::string text);
	const std::string name, text;
};

class registry
{
public:
	static registry& instance();
	void add_figure(figure fig);
	std::optional<figure> find(std::string proc, uint16_t chapter, std::string figure) const;
	const std::vector<figure>& figures() const;

	void add_macro(macro mac);
	std::optional<macro> find(std::string macro_name) const;
	const std::vector<macro>& macros() const;
private:
	static registry* _instance;
	registry();
	std::vector<figure> _figures;
	std::vector<macro> _macros;
};
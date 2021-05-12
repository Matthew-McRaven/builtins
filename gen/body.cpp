#include <iostream>
/*
 * So, why all the evil defines? Well, trying to embed files into an executable is really hard.
 * The library we are using, incbin, works by using inline asm generated from
 */
#if __has_include("io0/input.txt")
#define has_in 
INCBIN(in0_{dir_name}, st(__proc) "/" st(__name) "/io0/input.txt" );
#endif
#if __has_include("io0/output.txt")
#define has_out
INCBIN(out0_{dir_name}, st(__proc) "/" st(__name) "/io0/output.txt" );
#endif

/*
 * High order language files
 */
#ifdef has_c
INCBIN(c_{dir_name}, st(__proc) "/" st(__name) "/" st(__name) ".c" );
#endif

/*
 * Assembly language files
 */
#ifdef has_pep
INCBIN(pep_{dir_name}, st(__proc) "/" st(__name) "/" st(__name) ".pep" );
#endif
#ifdef has_pepl
INCBIN(pepl_{dir_name}, st(__proc) "/" st(__name) "/" st(__name) ".pepl" );
#endif

/*
 * Object code files
 */
#ifdef has_peph
INCBIN(peph_{dir_name}, st(__proc) "/" st(__name) "/" st(__name) ".peph" );
#endif
#ifdef has_pepb
INCBIN(pepb_{dir_name}, st(__proc) "/" st(__name) "/" st(__name) ".pepb" );
#endif
#ifdef has_pepo
INCBIN(pepo_{dir_name}, st(__proc) "/" st(__name) "/" st(__name) ".pepo" );
#endif



class register_{dir_name}{{
public:
	register_{dir_name}();
}} __register_{dir_name};

register_{dir_name}::register_{dir_name}()
{{
	// Collect the defined files as strings.
	std::map<element_type, std::string> elements;

	// HOL files
	#ifdef has_c
	elements[element_type::kC] = as_string(gc_{dir_name}Data, gc_{dir_name}Size);
	#endif

	// Assembly code files
	#ifdef has_pep
	elements[element_type::kPep] = as_string(gpep_{dir_name}Data, gpep_{dir_name}Size);
	#endif
	#ifdef has_pepl
	elements[element_type::kPepl] = as_string(gpepl_{dir_name}Data, gpepl_{dir_name}Size);
	#endif

	// Object code files
	#ifdef has_peph
	elements[element_type::kPeph] = as_string(gpeph_{dir_name}Data, gpeph_{dir_name}Size);
	#endif
	#ifdef has_pepb
	elements[element_type::kPepb] = as_string(gpepb_{dir_name}Data, gpepb_{dir_name}Size);
	#endif
	#ifdef has_pepo
	elements[element_type::kPepo] = as_string(gpepo_{dir_name}Data, gpepo_{dir_name}Size);
	#endif



	/*
	 * Collect tests.
	 */
	std::vector<test> tests;
	#ifdef has_out
	auto out0 = as_string(gout0_{dir_name}Data, gout0_{dir_name}Size);
	#ifdef in0gin0Data
	in0 = as_string(gin0_{dir_name}Data, gin0_{dir_name}Size)
	tests.emplace_back(test(out0, in0));
	#else
	tests.emplace_back(test(out0));
	#endif
	#endif

	auto fig = figure(st(__proc), __chapter, __fig_number, tests, elements);
	registry::instance().add_figure(fig);
}}

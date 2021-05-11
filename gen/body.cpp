
/*
 * So, why all the evil defines? Well, trying to embed files into an executable is really hard.
 * The library we are using, incbin, works by using inline asm generated from
 */
#if __has_include("io0/input.txt")
#define has_in 
INCBIN(in0, st(proc) "/" st(name) "/io0/input.txt" );
#endif
#if __has_include("io0/output.txt")
#define has_out
INCBIN(out0, st(proc) "/" st(name) "/io0/output.txt" );
#endif

/*
 * High order language files
 */
#ifdef has_c
INCBIN(c, st(proc) "/" st(name) "/" st(name) ".c" );
#endif

/*
 * Assembly language files
 */
#ifdef has_pep
INCBIN(pep, st(proc) "/" st(name) "/" st(name) ".pep" );
#endif
#ifdef has_pepl
INCBIN(pepl, st(proc) "/" st(name) "/" st(name) ".pepl" );
#endif

/*
 * Object code files
 */
#ifdef has_peph
INCBIN(peph, st(proc) "/" st(name) "/" st(name) ".peph" );
#endif
#ifdef has_pepb
INCBIN(pepb, st(proc) "/" st(name) "/" st(name) ".pepb" );
#endif
#ifdef has_pepo
INCBIN(pepo, st(proc) "/" st(name) "/" st(name) ".pepo" );
#endif



bool register_{dir_name}()
{{
	// Collect the defined files as strings.
	std::map<element_type, std::string> elements;

	// HOL files
	#ifdef has_c
	elements[element_type::kC] = as_string(gcData, gcEnd);
	#endif

	// Assembly code files
	#ifdef has_pep
	elements[element_type::kPep] = as_string(gpepData, gpepEnd);
	#endif
	#ifdef has_pepl
	elements[element_type::kPepl] = as_string(gpeplData, gpeplEnd);
	#endif

	// Object code files
	#ifdef has_peph
	elements[element_type::kPeph] = as_string(gpephData, gpephEnd);
	#endif
	#ifdef has_pepb
	elements[element_type::kPepb] = as_string(gpepbData, gpepbEnd);
	#endif
	#ifdef has_pepo
	elements[element_type::kPepo] = as_string(gpepoData, gpepoEnd);
	#endif



	/*
	 * Collect tests.
	 */
	std::vector<test> tests;
	#ifdef has_out
	auto out0 = as_string(gout0Data, gout0End);
	#ifdef in0gin0Data
	in0 = as_string(gin0Data, gin0End)
	tests.emplace_back(test(out0, in0));
	#else
	tests.emplace_back(test(out0));
	#endif
	#endif

	auto fig = figure(st(proc), chapter, fig_number, tests, elements);
	registry::instance().add_figure(fig);
	return true;
	
}}


auto reg = register_{dir_name}();

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
	elements[element_type::kC] = as_string(__{dir_name}_c, __{dir_name}_c_len);
	#endif

	// Assembly code files
	#ifdef has_pep
	elements[element_type::kPep] = as_string(__{dir_name}_pep, __{dir_name}_pep_len);
	#endif
	#ifdef has_pepl
	elements[element_type::kPepl] = as_string(__{dir_name}_pepl, __{dir_name}_pepl_len);
	#endif

	// Object code files
	#ifdef has_peph
	elements[element_type::kPeph] = as_string(__{dir_name}_peph, __{dir_name}_peph_len);
	#endif
	#ifdef has_pepb
	elements[element_type::kPepb] = as_string(__{dir_name}_pepb, __{dir_name}_pepb_len);
	#endif
	#ifdef has_pepo
	elements[element_type::kPepo] = as_string(__{dir_name}_pepo, __{dir_name}_pepo_len);
	#endif



	/*
	 * Collect tests.
	 */
	std::vector<test> tests;
	#ifdef has_out0
	
	auto out0 = as_string(__{dir_name}_io0_output_txt, __{dir_name}_io0_output_txt_len);
	#ifdef has_in0
	auto in0 = as_string(__{dir_name}_io0_input_txt, __{dir_name}_io0_input_txt_len);
	tests.emplace_back(test(out0, in0));
	#else
	tests.emplace_back(test(out0));
	#endif
	#endif

	auto fig = figure(st(__proc), __chapter, __fig_number, tests, elements);
	registry::instance().add_figure(fig);
}}

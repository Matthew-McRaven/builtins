#include "ex_registry.hpp"
class register_{macro_name}{{
public:
	register_{macro_name}();
}} __register_{macro_name};

register_{macro_name}::register_{macro_name}()
{{
	auto macro_text = as_string({macro_name}_pepm, {macro_name}_pepm_len);
	auto mac = macro("{macro_name}", macro_text);
	registry::instance().add_macro(mac);
}}
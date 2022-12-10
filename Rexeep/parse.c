#include "parse.h"
#include "parse_table.h"

void parse(char* inp) {
	fl_tree* fl_tree = fl_instance();
	hash_table* parse_table = generate_parse_table(get_rules(), fl_tree);

	run(inp, parse_table);
}

void run(char* inp, hash_table* parse_table) {
	char point;

	buffer_init_result buffers = init_buffers(inp);

	while (point = *inp++) {

	}
}

buffer_init_result init_buffers(char* inp) {
	string_stack* inp_buffer = ss_instance();
	ss_push(inp_buffer, "$");

	int inp_len = strlen(inp);
	for (size_t i = inp_len; i > 0; i--)
	{
		ss_push(inp_buffer, str_first(inp - i));
	}

	string_stack* symbol_stack = ss_instance();
	ss_push(symbol_stack, "$");
	ss_push(symbol_stack, "S");

	buffer_init_result res = { .input_buffer = inp_buffer, .symbol_stack = symbol_stack };

	return res;
}

char** get_rules() {
	char* rules[5] = {
		"S=^E$",
		"E=SE|#"
		"S=G|M",
		"G=(M)",
		"M=aM|#"
	};

	return rules;
}
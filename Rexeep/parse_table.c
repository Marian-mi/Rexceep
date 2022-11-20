#include "parse_table.h"
#include "hash_table.h"
#include "util.h"
#include "fl_tree.h"

hash_table* generate_parse_table(char** rules) {
	fl_tree* tree = fl_instance();
	create_fl_tree(tree, rules);
	ls_compute(tree, rules);

	hash_table* parse_table = ht_instance();

	char* rule;
	while (rule = *(rules++)) {
		char* left_hand = str_first(rule);
		rule += 2;

		List* first_set = list_instance();
		get_first_set(tree, left_hand, first_set);

		for (size_t fs_ind = 0; fs_ind < first_set->count; fs_ind++)
		{
			char* element = first_set->tape[fs_ind];

			if (is_terminal(element)) 
				parse_table->add(parse_table, *left_hand + *element, rule);
			else {

			}
		}
	}
}
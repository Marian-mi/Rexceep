#include "parse_table.h"
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

		fl_node* node = tree->node_ref_table->get(tree->node_ref_table, str_first(left_hand));

		for (size_t ncl_ind = 0; ncl_ind < node->children_count; ncl_ind++)
		{
			List* first_set = list_instance();
			get_first_set(tree, left_hand, first_set, &ncl_ind);
			for (size_t fs_ind = 0; fs_ind < first_set->count; fs_ind++)
			{
				char* element = first_set->tape[fs_ind];

				if (is_terminal(element))
					parse_table->add(parse_table, combine_chars(left_hand, element), rule);
				else if (*element == '#') {
					List* follow_set = ((ls_node*)tree->last_table->get(tree->last_table, left_hand))->terminals;

					for (size_t ls_ind = 0; ls_ind < follow_set->count; ls_ind++)
					{
						char* ls_el = (char*)follow_set->tape[ls_ind];
						if (*ls_el == '$')
							parse_table->add(parse_table, combine_chars(left_hand, "$"), rule);
						else
							parse_table->add(parse_table, combine_chars(left_hand, ls_el), "#");
					}
				}
			}
		}
	}

	return parse_table;
}
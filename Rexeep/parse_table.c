#include "parse_table.h"

char* get_prod(char* rule);
void inc_rule_to_next_prod(char** rule);

hash_table* generate_parse_table(char** rules, fl_tree* tree) {
	create_fl_tree(tree, rules);
	ls_compute(tree, rules);

	hash_table* parse_table = ht_instance();

	char* rule = malloc(sizeof(char*));
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
				char* element = (char*)first_set->tape[fs_ind];

				if (*element == '#') {
					List* follow_set = ((ls_node*)tree->last_table->get(tree->last_table, left_hand))->terminals;

					for (size_t ls_ind = 0; ls_ind < follow_set->count; ls_ind++)
					{
						char* ls_el = (char*)follow_set->tape[ls_ind];
						if (*ls_el == '$')
							parse_table->add(parse_table, combine_chars(left_hand, "$"), get_prod(rule));
						else
				 			parse_table->add(parse_table, combine_chars(left_hand, ls_el), "#");
					}
				}
				else if (is_terminal(*element)) {
					
					parse_table->add(parse_table, combine_chars(left_hand, element), get_prod(rule));
				}
			}

			inc_rule_to_next_prod(&rule);
		}
	}

	return parse_table;
}

char* get_prod(char* rule) {
	char* prod = calloc(strlen(rule), sizeof(char));

	if (prod == NULL) return;

	char rule_c;
	int ind = 0;
	while (rule_c = *rule++)
	{
		if (rule_c == '|') break;
		prod[ind] = rule_c;
		ind++;
	}
	prod[ind++] = (char)0;
	return prod;
}

void inc_rule_to_next_prod(char** rule) {
	char rule_c;
	while (rule_c = **rule)
	{
		*rule += 1;
		if (rule_c == '|') break;
	}
}
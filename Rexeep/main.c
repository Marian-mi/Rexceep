#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "util.h"
#include "fl_tree.h"
#include "parse_table.h"

#include "Stack.h"

#define LOGF 0

int main() {
	char* rules[7] = { "S=AkO", "A=aZ", "Z=BX|CX", "C=c", "B=bBC|r", "X=dX|#" };

	hash_table* parse_table = generate_parse_table(rules);

	char* rule = parse_table->get(parse_table, combine_chars("A", "a"));

	printf(rule);

	/*fl_tree"*",tree,= fl_instance();
	create_fl_tree(tree, rules);
	ls_compute(tree, rules);

	ls_node* ls = tree->last_table->get(tree->last_table, "X");

	for (size_t i = 0; i < ls->terminals->count; i++)
	{
		printf(ls->terminals->tape[i]);
	}*/
}

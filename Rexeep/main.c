#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "util.h"
#include "fl_tree.h"

#include "Stack.h"

int main() {
	char* rules[5] = { "S=ACB|Cbb|Ba", "B=da|BC", "C=g|#", "D=h|#" };

	fl_tree* tree = fl_instance();
	create_fl_tree(tree, rules);
	ls_compute(tree, rules);

	ls_node* noode = tree->last_table->get(tree->last_table, "B");

	for (size_t i = 0; i < noode->terminals->count; i++)
	{
		printf(((char*)noode->terminals->tape[i]));
	}
}

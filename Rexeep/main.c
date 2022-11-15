#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "util.h"
#include "fl_tree.h"

#include "Stack.h"

int main() {
	char* rules[7] = { "S=aBDh", "B=cC", "C=bC|#", "D=EF", "E=g|#", "F=f|#" };

	fl_tree* tree = fl_instance();
	create_fl_tree(tree, rules);
	ls_compute(tree, rules);

	ls_node* noode = tree->last_table->get(tree->last_table, "C");

	for (size_t i = 0; i < noode->terminals->count; i++)
	{
		printf(((char*)noode->terminals->tape[i]));
	}
}

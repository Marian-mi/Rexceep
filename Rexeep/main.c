#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "util.h"
#include "fl_tree.h"

#include "Stack.h"

#define LOGF 0

int main() {
	char* rules[7] = { "S=AkO", "A=aZ", "Z=BX|CX", "C=c", "B=bBC|r", "X=dX|#" };

	fl_tree* tree = fl_instance();
	create_fl_tree(tree, rules);
	ls_compute(tree, rules);

	ls_node* noode = tree->last_table->get(tree->last_table, "Z");

	if (LOGF) {
		List* fss = list_instance();
		get_first_set(tree, "D", fss);

		for (size_t i = 0; i < fss->count; i++)
		{
			printf(fss->tape[i]);
		}

		return 0;
	}

	for (size_t i = 0; i < noode->terminals->count; i++)
	{
		printf(((char*)noode->terminals->tape[i]));
	}
}

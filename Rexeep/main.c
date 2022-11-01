#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "util.h"
#include "fl_tree.h"

int main() {
	fl_tree* tree = fl_instance();

	char* rules[6] = { "S=E", "E=ZE|Z", "Z=R|M|x", "M=cM|c|a|h|w", "R=[M]" };

	create_fl_tree(tree, rules);

	List* set = list_instance();

	get_first_set(tree, "S", set);

	for (size_t i = 0; i < set->count; i++)
	{
		printf((char*)set->tape[i]);
	}
}

// a = 97, z = 122
// A = 65, Z = 90
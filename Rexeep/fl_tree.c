#include <stdio.h>
#include <stdlib.h>

#include "fl_tree.h"



fl_tree* fl_instance() {
	fl_tree* self = (fl_tree*)malloc(sizeof(fl_tree*));

	if (self == NULL)
		return NULL;

	self->node_ref_table = ht_instance();
	self->root = fl_create_node(self, "S");

	return self;
}

void create_fl_tree(fl_tree* tree, char** rules) {
	char* rule;

	while (rule = *rules++) {
		if (!(*rule)) break;
		parse_rule(tree, rule);
	}
}

void get_first_set(fl_tree* tree, char* symbol, List* set) {
	fl_node* node = tree->node_ref_table->get(tree->node_ref_table, str_first(symbol));

	for (size_t i = 0; i < node->children_count; i++)
	{
		fl_node* first_child = (fl_node*)((List*)node->children->tape[i])->tape[0];
		if (first_child->is_terminal == 1)
			list_add_unique(set, str_first(&first_child->symbol));
		else
			get_first_set(tree, &first_child->symbol, set);
	}
}

fl_node* fl_create_node(fl_tree* tree, char* symbol) {
	fl_node* node = malloc(sizeof(fl_node));

	if (node == NULL)
		return NULL;

	node->symbol = *symbol;
	node->children_count = 0;
	node->is_terminal = is_terminal(*symbol);

	if (!node->is_terminal)
		tree->node_ref_table->add(tree->node_ref_table, symbol, node);

	return node;
}

fl_node* fl_get_or_create_node(fl_tree* tree, char* sybmbol) {
	void* node = tree->node_ref_table->get(tree->node_ref_table, sybmbol);

	if (node)
		return (fl_node*)node;

	return fl_create_node(tree, sybmbol);
}

void parse_rule(fl_tree* tree, char* rule) {
	char* code;
	char* symbol = str_first(rule);
	rule += 2;
	List* children = list_instance();
	List* child_block = list_instance();

	while (code = rule++)
	{
		if (!(*code)) break;
		if (*code == '|') {
			list_add(children, child_block);
			child_block = list_instance();
		}
		else if (is_terminal(*code))
			list_add(child_block, fl_create_node(NULL, str_first(code)));
		else
			list_add(child_block, fl_get_or_create_node(tree, str_first(code)));
	}

	list_add(children, child_block);
	fl_get_or_create_node(tree, symbol)->children = children;
	fl_get_or_create_node(tree, symbol)->children_count = children->count;
}

int is_terminal(char code) {
	if ((int)code > 64 && (int)code < 91)
		return 0;

	return 1;
}
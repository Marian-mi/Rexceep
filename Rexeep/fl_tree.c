#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fl_tree.h"

void ls_parse_rule(fl_tree* tree, char* rule);
void ls_parse_prod(fl_tree* tree, char lhs, char* prod);

fl_tree* fl_instance() {
	fl_tree* self = (fl_tree*)malloc(sizeof(fl_tree*));

	if (self == NULL)
		return NULL;

	self->node_ref_table = ht_instance();
	self->last_table = ht_instance();
	self->root = fl_create_node(self, "S");

	return self;
}

typedef struct ls_node_ ls_node;

struct ls_node_
{
	List* terminal;
	List* non_terminals;
};

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

hash_table* ls_get(fl_tree* tree, char** rules) {
	char* rule;

	while (rule = *rules++) {
		if (!(*rule)) break;
		ls_parse_rule(tree, rule);
	}
}

void ls_parse_rule(fl_tree* tree, char* rule) {
	char lhs = *rule;
	rule += 2;
	ls_parse_prod(tree, lhs, rule);
}

void ls_parse_prod(fl_tree* tree, char lhs, char* prod) {
	char symbol;

	if (strlen(prod) == 1) {
		if (is_terminal(*prod))
			return;
		else {
			ls_node* node = ls_get_or_create_node(tree->last_table, prod);
			list_add(node->terminal, &symbol);
		}
	}

	char non_terminal = (char)0;
	while (symbol = *prod++)
	{
		if (is_terminal(symbol) && non_terminal) {
			 
		}
	}
}

ls_node* ls_get_or_create_node(hash_table* tbl, char* symbol) {
	ls_node* node = tbl->get(tbl, str_first(symbol));

	if (node) return node;

	node = malloc(sizeof(ls_node*));

	if (node == NULL) return NULL;

	node->terminal = list_instance();
	node->non_terminals = list_instance();

	tbl->add(tbl, symbol, node);

	return node;
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
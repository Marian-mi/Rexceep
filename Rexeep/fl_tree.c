#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fl_tree.h"
#include "Stack.h"


void ls_parse_rule(fl_tree* tree, char* rule);
ls_node* ls_get_or_create_node(hash_table* tbl, char* symbol);
void ls_parse_prod(fl_tree* tree, char lhs, char* prod);
void ls_finalize(fl_tree* tree, ls_node* node);

fl_tree* fl_instance() {
	fl_tree* self = (fl_tree*)malloc(sizeof(fl_tree*));

	if (self == NULL)
		return NULL;

	self->node_ref_table = ht_instance();
	self->last_table = ht_instance();
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
	if (is_terminal(*symbol)) {
		list_add(set, str_first(symbol));
		return;
	}

	fl_node* node = tree->node_ref_table->get(tree->node_ref_table, str_first(symbol));

	for (size_t i = 0; i < node->children_count; i++)
	{
		fl_node* child = NULL;
		int nc_ind = 0;
		List* ncl_children = ((List*)node->children->tape[i]);

		do {
			child = (fl_node*)(ncl_children->tape[nc_ind]);

			if (child->is_terminal == 1) {
				list_add_unique(set, str_first(&child->symbol));
				break;
			}
			else if (*str_first(symbol) != child->symbol)
				get_first_set(tree, &child->symbol, set);

			nc_ind++;
		} while (nc_ind < ncl_children->count && child->is_nullable);
	}

	for (size_t i = 0; i < set->count; i++)
	{
		if (*(char*)set->tape[i] == '#')
			node->is_nullable = 1;
	}
}

void ls_compute(fl_tree* tree, char** rules) {
	char* rule;
	List* symbols = list_instance();

	ls_node* firstNode = ls_get_or_create_node(tree->last_table, "S");
	list_add(firstNode->terminals, "$");

	while (rule = *rules++) {
		if (!(*rule)) break;
		ls_parse_rule(tree, rule, symbols);
	}

	for (size_t i = symbols->count - 1; i > 0; i--)
	{
		ls_finalize(tree, ls_get_or_create_node(tree->last_table, str_first(symbols->tape[i])));
	}
}

void ls_finalize(fl_tree* tree, ls_node* node) {
	for (size_t i = 0; i < node->non_terminals->count; i++)
	{
		ls_node* cnt_node = ls_get_or_create_node(tree->last_table, node->non_terminals->tape[i]);

		if (node == cnt_node) continue;

		if (cnt_node->non_terminals->count > 0)
			ls_finalize(tree, cnt_node);

		for (size_t cnt_ti = 0; cnt_ti < cnt_node->terminals->count; cnt_ti++)
		{
			list_add_unique(node->terminals, cnt_node->terminals->tape[cnt_ti]);
		}

	}
	node->non_terminals->count = 0;
}

void ls_parse_rule(fl_tree* tree, char* rule, List* symbols) {
	list_add(symbols, str_first(rule));

	char lhs = *rule;
	rule += 2;

	ls_parse_prod(tree, lhs, rule);
}

void ls_parse_prod(fl_tree* tree, char lhs, char* prod) {
	if (strlen(prod) == 1) {
		if (!is_terminal(*prod)) {
			ls_node* node = ls_get_or_create_node(tree->last_table, str_first(prod));
			list_add_unique(node->non_terminals, &lhs);
		}

		return;
	}

	char symbol;
	string_stack* nt_stack = ss_instance();

	while (symbol = *prod++)
	{
		if (symbol == '|') {
			ls_parse_prod(tree, lhs, prod);
			break;
		}

		if (is_terminal(symbol) && ss_is_empty(nt_stack) || symbol == '#')
			continue;

		if (!is_terminal(symbol) && ss_is_empty(nt_stack)) {
			ss_push(nt_stack, str_first(&symbol));
			continue;
		}

		if (is_terminal(symbol)) {
			for (size_t i = nt_stack->rear; i < nt_stack->front; i++)
			{
				ls_node* node = ls_get_or_create_node(tree->last_table, (char*)nt_stack->list->tape[i]);
				list_add(node->terminals, str_first(&symbol));
			}

			ss_clear(nt_stack);
			continue;
		}

		{
			fl_node* node = fl_get_or_create_node(tree, str_first(&symbol));
			List* first_list = list_instance();
			get_first_set(tree, str_first(&symbol), first_list);

			for (size_t i = nt_stack->rear; i < nt_stack->front; i++)
			{
				ls_node* node = ls_get_or_create_node(tree->last_table, (char*)nt_stack->list->tape[i]);

				for (size_t j = 0; j < first_list->count; j++)
				{
					if (*(char*)first_list->tape[j] == '#') continue;
					list_add(node->terminals, first_list->tape[j]);
				}
			}

			if (!node->is_nullable)
				ss_clear(nt_stack);

			ss_push(nt_stack, str_first(&symbol));

			free(first_list);
		}
	}

	if (!ss_is_empty(nt_stack)) {

		for (size_t i = nt_stack->rear; i < nt_stack->front; i++)
		{
			char* last_symbol = (char*)nt_stack->list->tape[i];
			ls_node* node = ls_get_or_create_node(tree->last_table, (char*)nt_stack->list->tape[i]);

			list_add(node->non_terminals, str_first(&lhs));
		}
	}
}

ls_node* ls_get_or_create_node(hash_table* tbl, char* symbol) {
	ls_node* node = tbl->get(tbl, str_first(symbol));

	if (node) return node;

	node = malloc(sizeof(ls_node*));

	if (node == NULL) return NULL;

	node->symbol = *str_first(symbol);
	node->terminals = list_instance();
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
	node->is_nullable = 0;
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
		else if (is_terminal(*code)) {
			list_add(child_block, fl_create_node(NULL, str_first(code)));
		}
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
#include "hash_table.h"
#include "Stack.h"


typedef struct fl_tree_ fl_tree;
typedef struct fl_node_ fl_node;
typedef struct ls_node_ ls_node;
//cfgTree cfgCreateTree(fl_node* root);

struct fl_tree_ {
	fl_node* root;
	hash_table* node_ref_table;
	hash_table* last_table;
};

struct fl_node_ {
	char symbol;
	List* children;
	int children_count;
	int is_terminal;
	int is_nullable;
};

struct ls_node_
{
	char symbol;
	List* terminals;
	List* non_terminals;
};

fl_node** fl_search_tree(char* symbol);
fl_node* fl_create_node(fl_tree* tree, char* symbol);
fl_node* fl_get_or_create_node(fl_tree* tree, char* sybmbol);
fl_tree* fl_instance();
void fl_add_node(fl_node* parent, fl_node* node);
void fl_add_children(char* parent_symbol, fl_node** children);

void create_fl_tree(fl_tree* tree, char** rules);
void parse_rule(fl_tree* tree, char* rule);
int is_terminal(char code);

void get_first_set(fl_tree* tree, char* symbol, List* set, int* ind);

void ls_compute(fl_tree* tree, char** rules);
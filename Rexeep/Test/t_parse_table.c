#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "t_parse_table.h"

void validate_follow_set(fl_tree* tree, char* sym, char* toBe);

int t_parse_table() {
	//printf("start parse table test\r\n");

	char* rules[7] = { "S=AkO", "A=aZ", "Z=BX|CX", "C=c", "B=bBC|r", "X=dX|#" };

	//printf("the rules:\r\n");

	for (size_t i = 0; i < 6; i++)
	{
		//printf(rules[i]);
		//printf("\r\n");
	}

	fl_tree* tree = fl_instance();

	hash_table* parse_table = generate_parse_table(rules, tree);

	return validate_table_result(parse_table, tree);
}

int validate_table_result(hash_table* tbl, fl_tree* tree) {
	int* passedCount = malloc(sizeof(int*));
	*passedCount = 0;

	validate_first_set(tree, "S", "a");
	validate_first_set(tree, "A", "a");
	validate_first_set(tree, "Z", "brc");
	validate_first_set(tree, "C", "c");
	validate_first_set(tree, "B", "br");
	validate_first_set(tree, "X", "d#");

	validate_follow_set(tree, "S", "$");
	validate_follow_set(tree, "A", "k");
	validate_follow_set(tree, "Z", "k");
	validate_follow_set(tree, "C", "dkc");
	validate_follow_set(tree, "B", "dck");
	validate_follow_set(tree, "X", "k");

	validate_table_item(tbl, "S", "a", "AkO", passedCount);
	validate_table_item(tbl, "A", "a", "aZ", passedCount);
	validate_table_item(tbl, "Z", "c", "CX", passedCount);
	validate_table_item(tbl, "Z", "b", "BX", passedCount);
	validate_table_item(tbl, "Z", "r", "BX", passedCount);
	validate_table_item(tbl, "C", "c", "c", passedCount);
	validate_table_item(tbl, "B", "b", "bBC", passedCount);
	validate_table_item(tbl, "B", "r", "r", passedCount);
	validate_table_item(tbl, "X", "k", "#", passedCount);
	validate_table_item(tbl, "X", "d", "dX", passedCount);

	if (*passedCount == 10) {
		//printf("%d table entries were tested\r\n", 10);
		//printf("test passed succesfully");
		return 1;
	}

	return 0;
}

void validate_first_set(fl_tree* tree, char* sumb, char* toBe) {
	List* list = list_instance();
	get_first_set(tree, sumb, list, NULL);

	char* fs = malloc(sizeof(char*));

	int ind = 0;
	for (ind; ind < list->count; ind++)
	{
		fs[ind] = *(char*)list->tape[ind];
	}
	fs[ind++] = (char)0;

	if (strcmp(fs, toBe) != 0) {
		printf("first set failed %s\r\n", sumb);
	}
}

void validate_follow_set(fl_tree* tree, char* sym, char* toBe) {
	ls_node* fs = (ls_node*)tree->last_table->get(tree->last_table, sym);
	
	char* fss = malloc(sizeof(char*));

	int ind = 0;
	for (ind; ind < fs->terminals->count; ind++)
	{
		fss[ind] = *(char*)fs->terminals->tape[ind];
	}
	fss[ind++] = (char)0;

	if (strcmp(fss, toBe) != 0) {
		printf("last set failed %s\r\n", sym);
	}
}

void validate_table_item(hash_table* tbl, char* lhs, char* term, char* should_equal_to, int *counter) {
	char* rule = tbl->get(tbl, combine_chars(lhs, term));

	if (rule == NULL) {
		printf("[%s][%s]\r\n", lhs, term);
		return 0;
	}

	if (strcmp(rule, should_equal_to) != 0) {
		//printf("Incorrect entry [%s][%s]\r\n", lhs, term);
		//printf("Shoulda been %s but it is %s", should_equal_to, rule);
	}
	else {
		(*counter)++;
	}
}

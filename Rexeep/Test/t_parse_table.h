#pragma once

#include "../parse_table.h"

int t_parse_table();

int validate_table_result(hash_table* tbl, fl_tree* tree);
void validate_first_set(fl_tree* tree, char* sumb, char* toBe);
void validate_table_item(hash_table* tbl, char* lhs, char* term, char* should_equal_to, int* counter);
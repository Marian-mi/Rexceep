#pragma once


typedef struct hash_table_ hash_table;
typedef struct ht_node_ ht_node;
typedef void (*ht_add_item)(hash_table* tbl, unsigned char* name, void* val);
typedef void* (*ht_get_item)(hash_table* tbl, unsigned char* name);
typedef void (*ht_free)(hash_table* self);

struct hash_table_ {
	int size;
	ht_node** tape;
	ht_add_item add;
	ht_get_item get;
	ht_free dispose;
	int count;
};

struct ht_node_ {
	char* name;
	ht_node* next;
	void* body;
};

hash_table* ht_instance();
#include <stdlib.h>

#include "hash_table.h"
#include "util.h"

static void add_item(hash_table* tbl, unsigned char* name, void* val) {
	tbl->tape[rcx_hash(name) % tbl->size] = val;
}

static void* get_item(hash_table* tbl, unsigned char* name) {
	return (tbl->tape[rcx_hash(name) % tbl->size]);
}

static void* get_or_add(hash_table* tbl, unsigned char* name, void* val) {
	void* nodeVal = get_item(tbl, name);

	if (nodeVal)
		add_item(tbl, name, val);
	
	return nodeVal;
}

static void dispose(hash_table* self) {
	free(self->tape);
	free(self);
}

hash_table* ht_instance() {
	hash_table* ins = (hash_table*)malloc(sizeof(hash_table));

	if (!ins) return NULL;

	ins->tape = calloc(30, sizeof(void*));
	ins->size = 30;
	ins->add = add_item;
	ins->get = get_item;
	ins->dispose = dispose;

	return ins;
}
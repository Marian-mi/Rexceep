#include <stdlib.h>

#include "hash_table.h"
#include <stdio.h>
#include <string.h>

static void add_item(hash_table* tbl, unsigned char* name, void* val) {
	ht_node* nodePtr = malloc(sizeof(ht_node*));

	nodePtr->body = val;
	nodePtr->name = name;
	nodePtr->next = NULL;

	int ind = rcx_hash(name) % tbl->size;

	if (tbl->tape[ind] == 0) {
		tbl->tape[ind] = nodePtr;
		tbl->count++;

		return;
	}

	ht_node* curr = (ht_node*)tbl->tape[ind];

	while (curr->next != NULL)
	{
		curr = (ht_node*)curr->next;
	}

	curr->next = nodePtr;
	tbl->count++;

	return;
}

static void* get_item(hash_table* tbl, unsigned char* name) {
	ht_node* current = (ht_node*)tbl->tape[rcx_hash(name) % tbl->size];

	if (current == NULL) return NULL;

	while (strcmp(name, current->name) != 0 && current->next != NULL) {
		current = current->next;
	}

	return current->body;
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

	ins->tape = calloc(30, sizeof(ht_node*));
	ins->size = 30;
	ins->add = add_item;
	ins->get = get_item;
	ins->dispose = dispose;
	ins->count = 0;

	return ins;
}
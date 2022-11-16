#pragma once

#include "util.h"

#pragma region string_stack

typedef struct string_stack_ string_stack;

string_stack* ss_instance();
void ss_push(string_stack* self, char* val);
char* ss_pop(string_stack* self);
char* ss_peek(string_stack* self);
void ss_dispose(string_stack* self);
int ss_is_empty(string_stack* self);
void ss_clear(string_stack* self);

struct string_stack_
{
	List* list;
	int rear;
	int front;
};

#pragma endregion


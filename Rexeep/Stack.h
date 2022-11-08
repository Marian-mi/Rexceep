#pragma once

#pragma region string_stack

typedef struct string_stack_ string_stack;

string_stack ss_instance(int size);
void ss_add(string_stack* self, char* val);
char* ss_pop(string_stack* self);
char* ss_peek(string_stack* self);
void ss_dispose(string_stack* self);

struct string_stack_
{
	char** tape;
	int rear;
	int front;
};

#pragma endregion


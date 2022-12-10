#pragma once


typedef struct buffer_init_result_ buffer_init_result;

struct buffer_init_result_
{
	string_stack* input_buffer;
	string_stack* symbol_stack;
};
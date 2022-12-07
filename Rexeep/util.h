#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct List_ List;

unsigned long
rcx_hash(unsigned char* str);

struct List_ {
    void** tape;
    int count;
    int max_size;
};

List* list_instance();

void* list_get(List* self, int index);
void list_add(List* self, void* val);
void list_dispose(List* self);

char* str_first(char* str);
char* combine_chars(char* one, char* other);
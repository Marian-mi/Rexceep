#include "util.h"
#include <string.h>
#include <stdio.h>

unsigned long
rcx_hash(unsigned char* str)
{
    unsigned long hash = 0;
    int c;

    while (c = *str++)
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

List* list_instance() {
    List* list = (List*)malloc(sizeof(List));

    if (list == NULL)
        return NULL;

    list->tape = calloc(sizeof(void *), 32);

    list->count = 0;
    list->max_size = 32;

    return list;
}

void list_add(List* self, void* val) {
    if (self->count >= self->max_size) {
        self->max_size = self->max_size * 2;
        void* newpos = realloc(self->tape, self->max_size);

        if (newpos == NULL)
            return;

        self->tape = newpos;
    }

    self->tape[self->count] = val;
    self->count = self->count++;
}

void list_add_unique(List* self, void* val) {
    if (self->count >= self->max_size) {
        self->max_size = self->max_size * 2;
        void* newpos = realloc(self->tape, self->max_size);

        if (newpos == NULL)
            return;

        self->tape = newpos;
    }

    for (size_t i = 0; i < self->count; i++)
    {
        if (*(char*)self->tape[i] == *(char*)val)
            return;
    }

    self->tape[self->count] = val;
    self->count = self->count++;
}

void* list_get(List* self, int index) {
    return (self->tape[index]);
}

void list_dispose(List* self) {
    free(self->tape);
    free(self);
}


char* str_first(char* str) {
    char* nstr = calloc(2, sizeof(char));
    if (nstr == NULL) return NULL;
    nstr[0] = *str;
    return nstr;
}


char* combine_chars(char* one, char* other) {
    char* res = calloc(3, sizeof(char));

    res[0] = (char)*one;
    res[1] = (char)*other;
    res[1] = (char)0;

    return res;
}
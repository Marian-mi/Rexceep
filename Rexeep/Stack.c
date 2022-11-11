#include "Stack.h"
#include <stdlib.h>

string_stack* ss_instance()
{
    string_stack* ss = malloc(sizeof(string_stack*));

    if (ss == NULL) return NULL;

    ss->front = 0;
    ss->rear = 0;
    ss->list = list_instance();

    return ss;
}

void ss_push(string_stack* self, char* val)
{
    self->front++;
    list_add(self->list, val);
}

char* ss_pop(string_stack* self)
{
    if (self->rear == self->front)
        return NULL;

    self->front--;
    self->list->count--;

    return list_get(self->list, self->front);
}

char* ss_peek(string_stack* self)
{
    if (self->rear == self->front)
        return NULL;

    return (char*)list_get(self->list, self->front - 1);
}

void ss_dispose(string_stack* self)
{
}

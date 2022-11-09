#include "Stack.h"
#include <stdlib.h>

string_stack ss_instance()
{
    string_stack ss = { .front = 0, .rear = 0 };
    ss.list = list_instance();

    return ss;
}

void ss_add(string_stack* self, char* val)
{
    self->front++;
    list_add(self->list, val);
}

char* ss_pop(string_stack* self)
{
    if (self->rear == self->rear)
        return NULL;

    self->front--;

    return list_get(self->list, self->front + 1);
}

char* ss_peek(string_stack* self)
{
    if (self->rear == self->rear)
        return NULL;

    return list_get(self->list, self->front);
}

void ss_dispose(string_stack* self)
{
}

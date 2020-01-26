#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

#include "deque.h"

#define NUM_DIRECTIONS (2)

struct deque {
    struct deque *next[NUM_DIRECTIONS];
    int value;
};

Deque *
dequeCreate(void)
{
    Deque *d;

    d = malloc(offsetof(struct deque, value));

    if(d) {
        d->next[DEQUE_FRONT] = d->next[DEQUE_BACK] = d;
    }

    return d;
}

void
dequePush(Deque *d, int direction, int value)
{
    Deque *e;

    assert(direction == DEQUE_FRONT || direction == DEQUE_BACK);

    e = malloc(sizeof(struct deque));
    assert(e);

    e->value = value;
    e->next[direction] = d->next[direction];
    e->next[!direction] = d;

    d->next[direction] = e;
    e->next[direction]->next[!direction] = e; /* preserves invariant */
}

int
dequePop(Deque *d, int direction)
{
    Deque *e;
    int ret;

    assert(direction == DEQUE_FRONT || direction == DEQUE_BACK);

    e = d->next[direction];

    if(e == d) {
        return DEQUE_EMPTY;
    }

    ret = e->value;

    d->next[direction] = e->next[direction];
    e->next[direction]->next[!direction] = d;

    free(e);

    return ret;
}

int
dequeIsEmpty(const Deque *d)
{
    return d->next[DEQUE_FRONT] == d;
}

void
dequeDestroy(Deque *d)
{
    while(!dequeIsEmpty(d)) {
        dequePop(d, DEQUE_FRONT);
    }

    free(d);
}

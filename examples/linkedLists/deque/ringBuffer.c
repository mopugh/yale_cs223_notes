#include <stdlib.h>
#include <assert.h>

#include "deque.h"

struct deque {
    size_t base;
    size_t length;
    size_t size;
    int *contents;
};

#define INITIAL_SIZE (8)

static Deque *
dequeCreateInternal(size_t size)
{
    struct deque *d;
    d = malloc(sizeof(struct deque));
    assert(d);

    d->base = 0;
    d->length = 0;
    d->size = size;

    d->contents = malloc(sizeof(int) * d->size);
    assert(d->contents);

    return d;
}

Deque *
dequeCreate(void)
{
    return dequeCreateInternal(INITIAL_SIZE);
}

void
dequePush(Deque *d, int direction, int value)
{
    struct deque *d2; // replacement deque if we grow
    int *oldContents; // old contents of d

    if(d->length == d->size) {
        // need to grow
        d2 = dequeCreateInternal(d->size * 2);

        // evacuate d
        while(!dequeIsEmpty(d)) {
            dequePush(d2, DEQUE_BACK, dequePop(d, DEQUE_FRONT));
        }

        // do a transplant of d2 to 2
        // save old contents to free them
        oldContents = d->contents;
        *d = *d2;

        // free pieces that are no longer needed
        free(oldContents);
        free(d2);
    }

    if(direction == DEQUE_FRONT) {
        if(d->base == 0) {
            d->base = d->size - 1;
        } else {
            d->base--;
        }

        d->length++;

        d->contents[d->base] = value;
    } else {
        d->contents[(d->base + d->length++) % d->size] = value;
    }
}

int
dequePop(Deque *d, int direction)
{
    int ret;

    if(dequeIsEmpty(d)) {
        return DEQUE_EMPTY;
    }

    if(direction == DEQUE_FRONT) {
        ret = d->contents[d->base];

        d->base = (d->base + 1) % d->size;
        d->length--;

        return ret;
    } else {
        return d->contents[(d->base + --d->length) % d->size];
    }
}

int
dequeIsEmpty(const Deque *d)
{
    return d->length == 0;
}

void
dequeDestroy(Deque *d)
{
    free(d->contents);
    free(d);
}

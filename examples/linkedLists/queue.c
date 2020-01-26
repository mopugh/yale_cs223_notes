#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* standard linked list element */
struct elt {
    struct elt *next;
    int value;
};

struct queue {
    struct elt *head; /* dequeue from this */
    struct elt *tail; /* enqueue from this */
};

/* create a new empty queue */
struct queue *
queueCreate(void)
{
    struct queue *q;

    q = malloc(sizeof(struct queue));
    assert(q);

    q->head = q->tail = 0;

    return q;
}

/* add a new value to back of queue */
void
enq(struct queue *q, int value)
{
    struct elt *e;

    e = malloc(sizeof(struct elt));
    assert(e);

    e->next = 0; /* Because I will be the tail, nobody is behind me */
    e->value = value;

    if(q->head == 0) {
        /* If the queue was empty, I become the head */
        q->head = e;
    } else {
        q->tail->next = e;
    }

    q->tail = e;
}

int
queueEmpty(const struct queue *q)
{
    return (q->head == 0);
}


/* remove and return value from front of queue */
int
deq(struct queue *q)
{
    struct elt *e;
    int ret;

    assert(!queueEmpty(q));

    ret = q->head->value;

    /* patch out the first element */
    e = q->head;
    q->head = e->next;

    free(e);

    return ret;
}

/* print contents of queue on a single line, head first */
void
queuePrint(const struct queue *q)
{
    struct elt *e;

    for(e = q->head; e != 0; e = e->next) {
        printf("%d ", e->value);
    }

    putchar('\n');
}

/* free a queue and all of its elements */
void
queueDestroy(struct queue *q)
{
    while(!queueEmpty(q)) {
        deq(q);
    }

    free(q);
}

int
main(int argc, char **argv)
{
    int i;
    struct queue *q;

    q = queueCreate();

    for(i = 0; i < 5; i++) {
        printf("enq %d\n", i);
        enq(q, i);
        queuePrint(q);
    }

    while(!queueEmpty(q)) {
        printf("deq gets %d\n", deq(q));
        queuePrint(q);
    }

    queueDestroy(q);

    return 0;
}

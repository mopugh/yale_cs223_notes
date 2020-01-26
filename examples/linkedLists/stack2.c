#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct elt {
    struct elt *next;
    int value;
};

struct stack {
    struct elt *head;
};

struct stack *
stackCreate(void)
{
    struct stack *s;

    s = malloc(sizeof(struct stack));
    assert(s);

    s->head = 0;

    return s;
}

void
stackPush(struct stack *s, int value)
{
    struct elt *e;

    e = malloc(sizeof(struct elt));
    assert(e);

    e->value = value;
    e->next = (*s).head;
    (*s).head = e;
}

int stackEmpty(const struct stack *s)
{
    return ((*s).head == 0);
}

int
stackPop(struct stack *s)
{
    struct elt *e;
    int ret;

    assert(!stackEmpty(s));

    e = (*s).head;
    ret = e->value;
    (*s).head = e->next;

    free(e);

    return ret;
}

void
stackPrint(const struct stack *s) {
    struct elt *e;

    for(e = (*s).head; e != 0; e = e->next){
        printf("%d ", e->value);
    }

    putchar('\n');
}

/* free a stack and all its elements */
void stackDestroy(struct stack *s)
{
    while(!stackEmpty(s)) {
        stackPop(s);
    }

    free(s);
}

int
main(int argc, char **argv)
{
    int i;
    struct stack *s;

    s = stackCreate();

    s->head = 0;

    for(i = 0; i < 5; i++) {
        printf("push %d\n", i);
        stackPush(s, i);
        stackPrint(s);
    }

    while(!stackEmpty(s)) {
        printf("pop gets %d\n", stackPop(s));
        stackPrint(s);
    }

    stackDestroy(s);

    return 0;
}

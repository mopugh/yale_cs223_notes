typedef struct deque Deque;

#define DEQUE_FRONT (0)
#define DEQUE_BACK (1)

#define DEQUE_EMPTY (-1) /* returned by dequePop if deque is empty */

/* return a new empty deque */
Deque *dequeCreate(void);

/* push a new value onto direction side of deque */
void dequePush(Deque *d, int direction, int value);

/* pop and return first value of direction side of deque d */
/* returns DEQUE_EMPTY if deque is empty */
int dequePop(Deque *d, int direction);

/* return 1 if deque is contains no elements, 0 otherwise */
int dequeIsEmpty(const Deque *d);

/* free space used by deque */
void dequeDestroy(Deque *d);

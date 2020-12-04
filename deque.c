#include <stdlib.h>
#include <assert.h>

struct ArrayDeque {
    int *_data;
    int _size;
    int _front;
    int _cap;
};

#define DEFAULT_CAPACITY 10

struct ArrayDeque *new_array_deque(int);
int len(struct ArrayDeque *);
int is_empty(struct ArrayDeque *);
int first(struct ArrayDeque *);
int last(struct ArrayDeque *);
void add_first(struct ArrayDeque *, int);
void add_last(struct ArrayDeque *, int);
struct ArrayDeque *resize(struct ArrayDeque *, int);
int delete_first(struct ArrayDeque *);
int delete_last(struct ArrayDeque *);

int main(void)
{
    struct ArrayDeque *D;
    int i;

    D = new_array_deque(DEFAULT_CAPACITY);
    for (i = 0; i < 20; i++)
        add_last(D, i);
    for (i = 0; i < 20; i++)
        assert(delete_last(D) == 19 - i);
    add_last(D, 5);
    add_first(D, 3);
    add_first(D, 7);
    assert(first(D) == 7);
    assert(delete_last(D) == 5);
    assert(len(D) == 2);
    assert(delete_last(D) == 3);
    assert(delete_last(D) == 7);
    add_first(D, 6);
    assert(last(D) == 6);
    add_first(D, 8);
    assert(is_empty(D) == 0);
    assert(last(D) == 6);
    for (i = 0; i < 20; i++)
        add_first(D, i);
    for (i = 0; i < 20; i++)
        assert(delete_first(D) == 19 - i);
    return 0;
}

struct ArrayDeque *new_array_deque(int capacity)
{
    struct ArrayDeque *D;

    D = (struct ArrayDeque *) malloc(sizeof(struct ArrayDeque));
    D->_data = (int *) malloc(sizeof(int) * capacity);
    D->_size = 0;
    D->_front = 0;
    return D;
}

int len(struct ArrayDeque *D)
{
    return D->_size;
}

int is_empty(struct ArrayDeque *D)
{
    return D->_size == 0;
}

int first(struct ArrayDeque *D)
{
    if (is_empty(D))
        return -1;
    return D->_data[D->_front];
}

int last(struct ArrayDeque *D)
{
    if (is_empty(D))
        return -1;
    return D->_data[(D->_front + D->_size - 1) % D->_cap];
}

void add_first(struct ArrayDeque *D, int val)
{
    if (D->_size == D->_cap)
        D = resize(D, 2 * D->_cap);
    D->_front = (D->_front + D->_cap - 1) % D->_cap;
    D->_data[D->_front] = val;
    D->_size++;
}

void add_last(struct ArrayDeque *D, int val)
{
    if (D->_size == D->_cap)
        D = resize(D, 2 * D->_cap);
    D->_data[(D->_front + D->_size - 1) % D->_cap] = val;
    D->_size++;
}

struct ArrayDeque *resize(struct ArrayDeque *D, int cap)
{
    struct ArrayDeque *old;
    int walk, i;
    
    old = D;
    D = new_array_deque(cap);
    walk = D->_front;
    for (i = 0; i < old->_size; i++) {
        D->_data[i] = old->_data[walk];
        walk = (walk + 1) % old->_cap;
    }
    D->_front = 0;
    D->_size = old->_size;
    free(old->_data);
    free(old);
    return D;
}

int delete_first(struct ArrayDeque *D)
{
    int val;

    if (is_empty(D))
        return -1;
    if (D->_size > 0 && D->_size < D->_cap / 4)
        D = resize(D, D->_cap / 2);
    val = D->_data[D->_front];
    D->_front = (D->_front + 1) % D->_cap;
    D->_size--;
    return val;
}

int delete_last(struct ArrayDeque *D)
{
    int val;

    if (is_empty(D))
        return -1;
    if (D->_size > 0 && D->_size < D->_cap / 4)
        D = resize(D, D->_cap / 2);
    val = D->_data[(D->_front + D->_size - 1) % D->_cap];
    D->_size--;
    return val;
}
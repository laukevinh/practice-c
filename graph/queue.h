struct Node {
    struct AdjList * data;
    struct Node * next;
};

struct Queue {
    struct Node * head;
    struct Node * tail;
};

struct Queue * new_queue(struct AdjList * data);
void delete_queue(struct Queue * q);
void enqueue(struct Queue * q, struct AdjList * data);
struct AdjList * dequeue(struct Queue * q);
int length(struct Queue * q);

void print_queue(struct Queue * q);

void test_queue(void);
void test_length(void);

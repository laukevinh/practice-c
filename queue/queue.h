struct Node {
    int data;
    struct Node * next;
    struct Node * prev;
};

struct Queue {
    struct Node * head;
    struct Node * tail;
};

struct Queue * new_queue(int data);
void delete_queue(struct Queue * q);
void enqueue(struct Queue * q, int data);
int dequeue(struct Queue * q);
int length(struct Queue * q);

void print_queue(struct Queue * q);

void test_queue(void);
void test_length(void);

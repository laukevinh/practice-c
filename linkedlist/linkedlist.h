struct Node {
    int data;
    struct Node * next;
};

struct LinkedList {
    struct Node * head;
};

struct LinkedList * new_list(void);
void delete_list(struct LinkedList * list);
int length(struct LinkedList * list);
int empty(struct LinkedList * list);
struct Node* node_at(struct LinkedList * list, int index);
void push_front(struct LinkedList * list, int data);
int pop_front(struct LinkedList * list);
void push_back(struct LinkedList * list, int data);
int pop_back(struct LinkedList * list);
int front(struct LinkedList * list);
int back(struct LinkedList * list);
void insert(struct LinkedList * list, int index, int data);
void erase(struct LinkedList * list, int index);
int value_n_from_end(struct LinkedList * list, int n);
void reverse(struct LinkedList * list);
void remove_value(struct LinkedList * list, int data);

void print_list(struct LinkedList * list);

void test_list(void);
void test_length(void);
void test_empty(void);
void test_value_at(void);
void test_push_front(void);
void test_pop_front(void);
void test_push_back(void);
void test_pop_back(void);
void test_front_back(void);

void test_reverse(void);

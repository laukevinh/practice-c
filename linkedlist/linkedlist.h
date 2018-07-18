struct Node {
    int data;
    struct Node * next;
};

struct LinkedList {
    struct Node * head;
};

struct LinkedList * new_linked_list(int data);
void delete_linked_list(struct LinkedList * linkedList);
void push(struct LinkedList * linkedList, int data);
int pop(struct LinkedList * linkedList);
int length(struct LinkedList * linkedList);
void reverse(struct LinkedList * linkedList);

void print_linked_list(struct LinkedList * linkedList);

void test_linked_list(void);
void test_length(void);
void test_reverse(void);

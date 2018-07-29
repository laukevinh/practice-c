struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct sNode {
    struct Node* node;
    struct sNode* next;
};

struct Stack {
    struct sNode* head;
};

struct Node* new_node(int i);
void insert(struct Node* node, int i);
void delete_tree(struct Node* node);
int is_in_tree(struct Node* node, int i);
int count(struct Node* node);
int height(struct Node* node);
int min(struct Node* node);
int max(struct Node* node);
struct Node* successor(struct Node* node, int i);
struct Node* delete_node(struct Node* node, int i);
void print_in_order(struct Node* node);

struct sNode* new_stack_node(struct Node* node);
struct Stack* new_stack(struct Node* node);
void append_stack(struct Stack* stack, struct Node* node);
struct Node* pop_stack(struct Stack* stack);
void delete_stack(struct Stack* stack);
void print_stack(struct Stack* stack);

/* tests */
void test_new_node(void);
void test_new_bst(void);
void test_insert(void);
void test_is_in_tree(void);
void test_count(void);
void test_height(void);
void test_min_max(void);
void test_successor(void);
void test_delete_node(void);
/*
void test_update(void);
void test_find(void);
*/

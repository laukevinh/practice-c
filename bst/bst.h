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

/* tests */
void test_new_node(void);
void test_new_bst(void);
void test_insert(void);
void test_is_in_tree(void);
void test_count(void);
void test_height(void);
void test_min(void);
void test_max(void);
void test_successor(void);
/*
void test_delete(void);
void test_update(void);
void test_find(void);
*/

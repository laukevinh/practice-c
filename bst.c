#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define max(A, B) ((A) > (B) ? (A) : (B))

struct Node {
    int val;
    int h;
    struct Node *left;
    struct Node *right;
};

struct Node *newnode(int);
int get_min(struct Node *);
int get_max(struct Node *);
struct Node *get(struct Node *, int);
int in_tree(struct Node *, int);
void print_inorder(struct Node *);
int get_node_count(struct Node *);
int get_height(struct Node *);
int get_h(struct Node *);
int is_bst(struct Node *);
int successor(struct Node *, int);
int predecessor(struct Node *, int);
struct Node *insert(struct Node *, int);
struct Node *del(struct Node *, int);
int is_avl(struct Node *);
void print_lvlorder(struct Node *);

int main(void)
{
    struct Node *tree, *bst, *avl;
    int vals[] = { 10, 20, 40, 30, 50, 60, 80, 70, 90, 100};
    int i, n;

    tree = newnode(i = 65);
    tree->left = newnode(80);
    assert(is_bst(tree) == 0);
    avl = newnode(i = 65);
    assert(avl->val == i);
    n = sizeof(vals) / sizeof(vals[0]);
    for (i = 0; i < n; i++)
        avl = insert(avl, vals[i]);
    assert(is_avl(avl) == 1);
    assert(get_min(avl) == vals[0]);
    assert(get_max(avl) == vals[n-1]);
    assert(get_node_count(avl) == n + 1);
    assert(get_height(avl) == 3);
    assert(get_h(avl) == 3);
    print_inorder(avl);
    printf("\n");
    avl = del(avl, 100);
    avl = del(avl, 10);
    assert(in_tree(avl, 10) == 0);
    assert(in_tree(avl, 80) == 1);
    assert(successor(avl, 60) == 65);
    assert(successor(avl, 20) == 30);
    assert(successor(avl, 90) == -1);
    assert(successor(avl, 10) == -1);
    assert(predecessor(avl, 65) == 60);
    assert(predecessor(avl, 30) == 20);
    assert(predecessor(avl, 20) == -1);
    assert(predecessor(avl, 10) == -1);
    assert(is_bst(avl) == 1);
    assert(is_avl(avl) == 1);
    print_inorder(avl);
    printf("\n");
    print_lvlorder(avl);
    printf("\n");
    return 0;
}

struct Node *newnode(int val)
{
    struct Node *node;

    node = (struct Node *) malloc(sizeof(struct Node));
    node->val = val;
    node->h = 0;
    node->left = node->right = NULL;
    return node;
}

struct Node *get_min_node(struct Node *root)
{
    if (root == NULL)
        return root;
    while (root->left != NULL)
        root = root->left;
    return root;
}

struct Node *get_max_node(struct Node *root)
{
    if (root == NULL)
        return root;
    while (root->right != NULL)
        root = root->right;
    return root;
}

int get_min(struct Node *root)
{
    struct Node *min;

    min = get_min_node(root);
    return (min == NULL) ? -1 : min->val;
}

int get_max(struct Node *root)
{
    struct Node *max;

    max = get_max_node(root);
    return (max == NULL) ? -1 : max->val;
}

struct Node *get(struct Node *root, int val)
{
    if (root == NULL)
        return NULL;
    else if (val < root->val)
        return get(root->left, val);
    else if (val > root->val)
        return get(root->right, val);
    else
        return root;
}

int in_tree(struct Node *root, int val)
{
    return (get(root, val) == NULL) ? 0 : 1;
}

void print_inorder(struct Node *root)
{
    if (root != NULL) {
        print_inorder(root->left);
        printf("%d ", root->val);
        print_inorder(root->right);
    }
}

int get_node_count(struct Node *root)
{
    int i;

    i = 0;
    if (root != NULL) {
        i += get_node_count(root->left);
        i += get_node_count(root->right);
        i += 1;
    }
    return i;
}

/* get_height: calculates height of Node */
int get_height(struct Node *root)
{
    int lefth, righth, maxh;

    if (root == NULL)
        return -1;
    lefth = get_height(root->left);
    righth = get_height(root->right);
    maxh = (lefth > righth) ? lefth : righth;
    return maxh + 1;
}

/* get_h: returns height field of Node */
int get_h(struct Node *root)
{ 
    return (root == NULL) ? -1 : root->h;
}

int is_bst(struct Node *root)
{
    enum boolean { FALSE, TRUE };

    if (root == NULL)
        return TRUE;
    if (root->left != NULL && root->left->val > root->val)
        return FALSE;
    if (root->right != NULL && root->right->val < root->val)
        return FALSE;
    if (!is_bst(root->left) || !is_bst(root->right))
        return FALSE;
    return TRUE;
}

void update_height(struct Node *root)
{
    root->h = 1 + max(get_h(root->left), get_h(root->right));
}

/* successor_node:  find next larger node */
/* psuedocode:
    once you find node containing target value
    if node has right child
        return min node in right child tree
    else 
        return first ancestor larger than target value */
/* alternatively: 
    if target value < current node and >= left child,
    check if there is successor in left child. If not,
    return current node, the parent of the target value */
struct Node *successor_node(struct Node *root, int val)
{
    struct Node *node;

    if (root == NULL)
        return NULL;
    if (val < root->val) {
        if (root->left != NULL)
            if (val >= root->left->val) {
                node = successor_node(root->left, val);
                return node ? node : root;
            }
        return successor_node(root->left, val);
    } else if (val > root->val)
        return successor_node(root->right, val);
    else {
        return get_min_node(root->right);
    }
}

int successor(struct Node *root, int val)
{
    struct Node *node;

    return (node = successor_node(root, val)) ? node->val : -1;
}

struct Node *predecessor_node(struct Node *root, int val)
{
    struct Node *node;

    if (root == NULL)
        return NULL;
    if (val < root->val)
        return predecessor_node(root->left, val);
    else if (val > root->val) {
        if (root->right != NULL)
            if (val <= root->right->val) {
                node = predecessor_node(root->right, val);
                return node ? node : root;
            }
        return predecessor_node(root->right, val);
    } else {
        return get_max_node(root->left);
    }
}

int predecessor(struct Node *root, int val)
{
    struct Node *node;

    return (node = predecessor_node(root, val)) ? node->val : -1;
}

/* balance: returns left vs right child height */
int balance(struct Node *node)
{
    if (node == NULL)
        return 0;
    return get_h(node->right) - get_h(node->left);
}

/* Rotations:
    A, B and C are subtrees of the tree rooted with
    y (on the left side) or x (on the right side)

        y                               x
       / \     Right Rotation          / \
      x   C    - - - - - - - >        A   y 
     / \       < - - - - - - -           / \
    A   B      Left Rotation            B   C
    
    Keys in both trees follow the this order
    keys(A) < key(x) < keys(B) < key(y) < keys(C)
    So BST property is not violated anywhere. */

/* leftrot: see diagram above. LR(x) returns y. */
struct Node *leftrot(struct Node *x)
{
    struct Node *y, *B;

    y = x->right;
    B = y->left;
    y->left = x;
    x->right = B;
    update_height(x);
    update_height(y);
    return y;
}

/* rightrot: see diagram above. RR(y) returns x. */
struct Node *rightrot(struct Node *y)
{
    struct Node *x, *B;

    x = y->left;
    B = x->right;
    x->right = y;
    y->left = B;
    update_height(y);
    update_height(x);
    return x;
}

/* Insertions: 
    Perform normal BST insert, then update height because
    children height might have changed. Check if AVL 
    property is violated (i.e. height of left vs right child
    not within 1) and fix via rotations. There are 4 cases. 
    
    1.) Right-right case
        x                            y
       / \                         /   \ 
      A   y     LeftRotate(y)     x     z
         / \    - - - - - - >    / \   / \
        B   z                   A   B C   D
           / \
          C   D 
    
    2.) Right-left case
        x                         x                           y
       / \                       / \                        /   \ 
      A   z   RightRotate(z)    A   y     LeftRotate(y)    x     z
         / \  - - - - - - ->       / \    - - - - - - >   / \   / \
        y   D                     B   z                  A   B C   D
       / \                           / \
      B   C                         C   D                         
    
    3.) Left-left case is mirror above.
    4.) Left-right case is mirror above. */

/* insert: perform normal BST insert, then fix AVL
    property if violated. Explanation above. */
struct Node *insert(struct Node *root, int val)
{
    if (root == NULL)
        return newnode(val);
    if (val < root->val)
        root->left = insert(root->left, val);
    else                                /* val >= root->val */
        root->right = insert(root->right, val);
    update_height(root);                /* children heights might have changed */
    if (balance(root) > 1) {            /* if right heavy */
        if (balance(root->right) < -1)  /* fix right-left to right-right case */
            root->right = rightrot(root->right);
        root = leftrot(root);           /* fix right-right case */
    } else if (balance(root) < -1) {    /* mirror version of above */
        if (balance(root->left) > 1)
            root->left = leftrot(root->left);
        root = rightrot(root);
    }
    return root;
}

/* del: don't need parent pointer because recursive implementation 
    updates from bottom up, so ancestors get latest info. */
struct Node *del(struct Node *node, int val)
{
    struct Node *temp;

    if (node == NULL)
        return NULL;
    else if (val < node->val)
        node->left = del(node->left, val);
    else if (val > node->val)
        node->right = del(node->right, val);
    else {  /* target val found */
        if (node->left == NULL || node->right == NULL) { /* leaf or single child */
            temp = node->left ? node->left : node->right;
            free(node);
            return temp;    /* return single child or NULL */
        } else {            /* 2 children, get successor */
            node->val = get_min(node->right);
            node->right = del(node->right, node->val);
        }
    }
    update_height(node);    /* same logic as last half of insert */
    if (balance(node) > 1) {
        if (balance(node->right) < -1)
            node->right = rightrot(node->right);
        node = leftrot(node);
    } else if (balance(node) < -1) {
        if (balance(node->left) > 1)
            node->left = leftrot(node->left);
        node = rightrot(node);
    }
    return node;
}

int balanced(struct Node *root)
{
    int diff;

    diff = get_h(root->left) - get_h(root->right);
    diff *= (diff < 0) ? -1 : 1;
    return (diff <= 1);
}

int is_avl(struct Node *root)
{
    enum boolean { FALSE, TRUE };

    if (root != NULL) {
        if (!balanced(root)
                || !is_avl(root->left)
                || !is_avl(root->right))
            return FALSE;
    }
    return TRUE;
}

struct QueueNode {
    struct Node *node;
    struct QueueNode *next;
};

struct Queue {
    struct QueueNode *head;
    struct QueueNode *tail;
};

struct Queue *enqueue(struct Queue *, struct Node *);
struct Node *dequeue(struct Queue *);
int empty(struct Queue *);

void print_lvlorder(struct Node *root)
{
    struct Node *node;
    struct Queue queue = { NULL, NULL };
    struct Queue *q = &queue;

    enqueue(q, root);
    while (!empty(q)) {
        node = dequeue(q);
        printf("%d ", node->val);
        if (node->left != NULL)
            enqueue(q, node->left);
        if (node->right != NULL)
            enqueue(q, node->right);
    }
}

struct QueueNode *newqnode(struct Node *node)
{
    struct QueueNode *qnode;

    qnode = (struct QueueNode *) malloc(sizeof(struct QueueNode));
    qnode->node = node;
    qnode->next = NULL;
    return qnode;
}

struct Queue *enqueue(struct Queue *q, struct Node *node)
{
    if (q == NULL)
        return NULL;
    if (q->tail == NULL)
        q->head = q->tail = newqnode(node);
    else {
        q->tail->next = newqnode(node);
        q->tail = q->tail->next;
    }
    return q;
}

struct Node *dequeue(struct Queue *q)
{
    struct Node *node;
    struct QueueNode *qnode;

    if (q == NULL || q->head == NULL)
        return NULL;
    node = q->head->node;
    qnode = q->head->next;
    free(q->head);
    q->head = qnode;
    if (qnode == NULL)
        q->tail = q->head;
    return node;
}

int empty(struct Queue *q)
{
    return (q == NULL || q->head == NULL);
}
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define max(A, B) (((A) > (B)) ? (A) : (B))

struct Node {
    int val;
    int h;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
};

struct Node *newnode(int);
struct Node *simple_insert(struct Node *, int);
struct Node *get_min_node(struct Node *);
int get_min(struct Node *);
int get_max(struct Node *);
struct Node *get(struct Node *, int);
int in_tree(struct Node *, int);
void print_inorder(struct Node *);
int get_node_count(struct Node *);
int get_height(struct Node *);
int get_h(struct Node *);
struct Node *simple_rm(struct Node *, int);
struct Node *successor_node(struct Node *, int);
int successor(struct Node *, int);
struct Node *predecessor_node(struct Node *, int);
int predecessor(struct Node *, int);
struct Node *leftrot(struct Node *);
struct Node *rightrot(struct Node *);
struct Node *insert(struct Node *, int);
int is_avl(struct Node *);
void print_lvlorder(struct Node *);

int main(void)
{
    struct Node *bst, *avl;
    int vals[] = { 10, 20, 40, 30, 50, 60, 80, 70, 90, 100};
    int i, n;

    bst = newnode(i = 65);
    assert(bst->val == i);
    assert(get_min_node(bst) == bst);
    n = sizeof(vals) / sizeof(vals[0]);
    for (i = 0; i < n; i++)
        simple_insert(bst, vals[i]);
    assert(is_avl(bst) == 0);
    assert(get_min(bst) == vals[0]);
    assert(get_max(bst) == vals[n-1]);
    assert(get_node_count(bst) == n + 1);
    assert(get_height(bst) == 5);
    assert(get_h(bst) == 5);
    print_inorder(bst);
    printf("\n");
    simple_rm(bst, 100);
    simple_rm(bst, 10);
    assert(get_height(bst) == 4);
    assert(get_h(bst) == 4);
    assert(in_tree(bst, 10) == 0);
    assert(in_tree(bst, 80) == 1);
    assert(successor(bst, 60) == 65);
    assert(successor(bst, 20) == 30);
    assert(successor(bst, 90) == -1);
    assert(successor(bst, 10) == -1);
    assert(predecessor(bst, 65) == 60);
    assert(predecessor(bst, 30) == 20);
    assert(predecessor(bst, 20) == -1);
    assert(predecessor(bst, 10) == -1);
    assert(is_avl(bst) == 0);
    print_inorder(bst);
    printf("\n");
    print_lvlorder(bst);
    printf("\n");
    avl = newnode(65);
    for (i = 0; i < n; i++)
        avl = insert(avl, vals[i]);
    print_inorder(avl);
    printf("\n");
    print_lvlorder(avl);
    printf("\n");
    assert(get_height(avl) == 3);
    assert(is_avl(avl) == 1);
    return 0;
}

struct Node *newnode(int val)
{
    struct Node *node;

    node = (struct Node *) malloc(sizeof(struct Node));
    node->val = val;
    node->h = 0;
    node->parent = node->left = node->right = NULL;
    return node;
}

struct Node *simple_insert(struct Node *root, int val)
{
    if (root == NULL)
        return newnode(val);
    if (val < root->val) {
        root->left = simple_insert(root->left, val);
        root->left->parent = root;
    } else {
        root->right = simple_insert(root->right, val);
        root->right->parent = root;
    }
    root->h = 1 + max(get_h(root->left), get_h(root->right));
    return root;
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

void update_heights(struct Node *root)
{
    for ( ; root != NULL ; root = root->parent)
        root->h = 1 + max(get_h(root->left), get_h(root->right));
}

/* repl_child: replaces parent's child from a to b */
void repl_child
(struct Node *parent, struct Node *a, struct Node *b)
{
    if (parent->left == a)
        parent->left = b;
    else if (parent->right == a)
        parent->right = b;
}

struct Node *simple_rm(struct Node *root, int val)
{
    struct Node *node;
    struct Node *marker; /* marks where to start update height */

    if (root == NULL)
        return NULL;
    else if (val < root->val)
        simple_rm(root->left, val);
    else if (val > root->val)
        simple_rm(root->right, val);
    else {  /* val == root->val */
        if (root->right == NULL) {  /* covers leaf case too */
            marker = root->parent;
            if ((node = root->left) != NULL)
                node->parent = root->parent;
            repl_child(root->parent, root, node);
        } else {
            node = get_min_node(root->right);
            if (node == root->right) {
                marker = node;
                node->parent = root->parent;
                repl_child(root->parent, root, node);
                node->left = root->left;
                if (root->left != NULL)
                    root->left->parent = node;
            } else {
                marker = node->parent; /* update height from here */
                node->parent->left = node->right;
                if (node->right != NULL)
                    node->right->parent = node->parent;
                node->parent = root->parent;
                repl_child(root->parent, root, node);
                node->left = root->left;
                if (root->left != NULL)
                    root->left->parent = node;
                node->right = root->right;
                if (root->right != NULL)
                    root->right->parent = node;
            }
        }
        update_heights(marker);
        free(root);
        return node;
    }
    return root;
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
        node = get_min_node(root->right);
        return node ? node : NULL;
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
        node = get_max_node(root->left);
        return node ? node : NULL;
    }
}

int predecessor(struct Node *root, int val)
{
    struct Node *node;

    return (node = predecessor_node(root, val)) ? node->val : -1;
}

struct Node *leftrot(struct Node *root)
{
    struct Node *pivot, *parent;

    if (root == NULL || (pivot = root->right) == NULL)
        return NULL;
    parent = root->parent;
    pivot->parent = parent;
    if (parent != NULL) {
        if (parent->left == root)
            parent->left = pivot;
        else
            parent->right = pivot;
    }
    root->parent = pivot;
    root->right = pivot->left;
    if (root->right != NULL)
        root->right->parent = root;
    pivot->left = root;
    root->h = 1 + max(get_h(root->left), get_h(root->right));
    pivot->h = 1 + max(get_h(pivot->left), get_h(pivot->right));
    return pivot;
}

struct Node *rightrot(struct Node *root)
{
    struct Node *pivot, *parent;

    if (root == NULL || (pivot = root->left) == NULL)
        return NULL;
    parent = root->parent;
    pivot->parent = parent;
    if (parent != NULL) {
        if (parent->left == root)
            parent->left = pivot;
        else
            parent->right = pivot;
    }
    root->parent = pivot;
    root->left = pivot->right;
    if (root->left != NULL)
        root->left->parent = root;
    pivot->right = root;
    root->h = 1 + max(get_h(root->left), get_h(root->right));
    pivot->h = 1 + max(get_h(pivot->left), get_h(pivot->right));
    return pivot;
}

struct Node *insert(struct Node *root, int val)
{
    if (root == NULL)
        return newnode(val);
    if (val < root->val) {
        root->left = insert(root->left, val);
        root->left->parent = root;
    } else {
        root->right = insert(root->right, val);
        root->right->parent = root;
    }
    root->h = 1 + max(get_h(root->left), get_h(root->right));
    if (get_h(root) - get_h(root->left) > 2) {
        if (get_h(root->right->right) >= get_h(root->right->left))
            return leftrot(root);
        else {
            root->right = rightrot(root->right);
            return leftrot(root);
        }
    } else if (get_h(root) - get_h(root->right) > 2) {
        if (get_h(root->left->left) >= get_h(root->left->right))
            return rightrot(root);
        else {
            root->left = leftrot(root->left);
            return rightrot(root);
        }
    }
    return root;
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
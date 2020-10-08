#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
struct Node *simple_rm(struct Node *, int);

int main(void)
{
    struct Node *root;
    int vals[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int i, n;

    root = newnode(i = 65);
    assert(root->val == i);
    assert(get_min_node(root) == root);
    n = sizeof(vals) / sizeof(vals[0]);
    for (i = 0; i < n; i++)
        simple_insert(root, vals[i]);
    assert(get_min(root) == vals[0]);
    assert(get_max(root) == vals[n-1]);
    assert(get_node_count(root) == n + 1);
    assert(get_height(root) == 6);
    print_inorder(root);
    printf("\n");
    simple_rm(root, 100);
    simple_rm(root, 10);
    print_inorder(root);
    printf("\n");
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

int get_min(struct Node *root)
{
    struct Node *min;

    min = get_min_node(root);
    return (min == NULL) ? -1 : min->val;
}

int get_max(struct Node *root)
{
    if (root == NULL)
        return -1;
    while (root->right != NULL)
        root = root->right;
    return root->val;
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

struct Node *simple_rm(struct Node *root, int val)
{
    struct Node *node;

    if (root == NULL)
        return NULL;
    else if (val < root->val)
        root->left = simple_rm(root->left, val);
    else if (val > root->val)
        root->right = simple_rm(root->right, val);
    else {  /* val == root->val */
        if (root->right == NULL) {
            if ((node = root->left) != NULL)
                node->parent = root->parent;
        } else {
            node = get_min_node(root->right);
            if (node == root->right) {
                node->parent = root->parent;
                node->left = root->left;
                if (root->left != NULL)
                    root->left->parent = node;
            } else {
                node->parent->left = node->right;
                if (node->right != NULL)
                    node->right->parent = node->parent;
                node->parent = root->parent;
                node->left = root->left;
                if (root->left != NULL)
                    root->left->parent = node;
                node->right = root->right;
                if (root->right != NULL)
                    root->right->parent = node;
            }
        }
        free(root);
        return node;
    }
    return root;
}
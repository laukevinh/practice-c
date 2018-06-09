#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#define TRUE 1
#define FALSE 0

struct Node* new_node(int i)
{
    struct Node* node = malloc(sizeof(struct Node));
    node->data = i;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void delete_node(struct Node* node)
{
    /* this will free node data, but children
       are still in the heap */
    free(node);
}

void insert(struct Node* node, int i)
{
    if (i < node->data) {
        if (node->left == NULL)
            node->left = new_node(i);
        else
            insert(node->left, i);
    } else if (i > node->data) {
        if (node->right == NULL)
            node->right = new_node(i);
        else
            insert(node->right, i);
    } else {
        printf("Key exists\n");
    }
}

void delete_tree(struct Node* node)
{
    if (node->left != NULL)
        delete_tree(node->left);
    if (node->right != NULL)
        delete_tree(node->right);
    free(node);
}

int is_in_tree(struct Node* node, int i)
{
    if (i == node->data) {
        return TRUE;
    } else if (i < node->data && node->left != NULL) {
        is_in_tree(node->left, i);
    } else if (i > node->data && node->right != NULL) {
        is_in_tree(node->right, i);
    } else {
        return FALSE;
    }
}

int count(struct Node* node)
{
    if (node == NULL)
        return 0;
    return 1 + count(node->left) + count(node->right);
}

int height(struct Node* node)
{
    // height is 1 + max of children heights
    if (node == NULL)
        return -1;
    int hleft = height(node->left);
    int hright = height(node->right);
    return 1 + (hleft > hright ? hleft : hright);
}

int min(struct Node* node)
{
    while (node->left != NULL)
        node = node->left;
    return node->data;
}

int max(struct Node* node)
{
    while (node->right != NULL)
        node = node->right;
    return node->data;
}

struct sNode* new_stack_node(struct Node* node)
{
    struct sNode* snode = malloc(sizeof(struct sNode));
    snode->node = node;
    snode->next = NULL;
    return snode;
}

struct Stack* new_stack(struct Node* node)
{
    struct Stack* stack = malloc(sizeof(struct Stack));
    stack->head = new_stack_node(node);
    return stack;
}

void append_stack(struct Stack* stack, struct Node* node)
{
    struct sNode* new_snode = new_stack_node(node);
    new_snode->next = stack->head;
    stack->head = new_snode;
}

struct Node* pop_stack(struct Stack* stack)
{
    if (stack->head == NULL)
        return NULL;
    struct sNode* snode = stack->head;
    stack->head = snode->next;
    struct Node* node = snode->node;
    free(snode);
    return node;
}

void delete_stack(struct Stack* stack)
{
    while (stack->head != NULL)
        pop_stack(stack);
}

void print_stack(struct Stack* stack)
{
    struct sNode* snode = stack->head;
    for ( ; snode != NULL; snode = snode->next)
        printf("%d ", snode->node->data);
}

int successor(struct Node* node, int i)
{
    //struct Node* successor = NULL;
    // in order traversal
    // stack all left
    struct Stack* stack = new_stack(node);
    for ( ; node->left != NULL; node = node->left)
        append_stack(stack, node->left);
    // crawl = pop stack
    struct Node* curr = pop_stack(stack);
    // if right exists, curr = right 
    // if curr left exists, stack curr, curr go left
    // else curr = pop stack
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->right;
        if (curr != NULL) {
            while (curr->left != NULL) {
                append_stack(stack, curr);
                curr = curr->left;
            }
            printf("%d ", curr->data);
        }
        curr = pop_stack(stack);
    }
    /*
    if (curr->data == i)
        successor = pop_stack(stack)->data;
    */
    // get next in stack
    //print_stack(stack);
    delete_stack(stack);
    //return successor;
}

void print_in_order(struct Node* node)
{
    if (node->left != NULL)
        print_in_order(node->left);
    printf("%d ", node->data);
    if (node->right !=NULL)
        print_in_order(node->right);
}

void test_new_node(void)
{
    struct Node* root = new_node(0);
    printf("New Node: (%p) %d\n\n", root, root->data);
    delete_node(root);
}

void test_insert(void)
{
    struct Node* root = new_node(10);
    printf("Test insert\n");
    insert(root, 5);
    insert(root, 15);
    printf("%d %d %d\n\n", root->left->data, root->data, root->right->data);
    delete_node(root->left);
    delete_node(root->right);
    delete_node(root);
}

void test_is_in_tree(void)
{
    struct Node* root = new_node(10);
    printf("Test is in tree\n");
    for (int i=0; i<20; i+=4)
        insert(root, i);
    print_in_order(root);
    printf("\n");
    for (int i=0; i<30; i+=10)
        printf("%d %sin tree\n", i, is_in_tree(root, i) ? "" : "not ");
    printf("\n");
    delete_tree(root);
}

void test_count(void)
{
    struct Node* root = new_node(10);
    printf("Test count\n");
    for (int i=0; i<20; i+=4)
        insert(root, i);
    print_in_order(root);
    printf("Count: %d\n\n", count(root));
    delete_tree(root);
}

void test_height(void)
{
    struct Node* root = new_node(10);
    printf("Test height\n");
    for (int i=0; i<20; i+=4)
        insert(root, i);
    print_in_order(root);
    printf("Height: %d\n\n", height(root));
    delete_tree(root);
}

void test_min(void)
{
    struct Node* root = new_node(10);
    printf("Test min\n");
    for (int i=-4; i<20; i+=4)
        insert(root, i);
    print_in_order(root);
    printf("Min: %d\n\n", min(root));
    delete_tree(root);
}

void test_max(void)
{
    struct Node* root = new_node(10);
    printf("Test max\n");
    for (int i=4; i<20; i+=4)
        insert(root, i);
    print_in_order(root);
    printf("Max: %d\n\n", max(root));
    delete_tree(root);
}

void test_successor(void)
{
    struct Node* root = new_node(8);
    printf("Test successor\n");
    int a[5] = { 6, 16, 5, 7, 10 };
    for (int i=0; i<5; i++)
        insert(root, a[i]);
    print_in_order(root);
    printf("\nSuccessor: ");
    /*
    int s = successor(root, 5);
    printf("(%d,%d) ", 5, s);
    */
    for (int i=5; i<9; i++)
        //printf("(%d,%d) ", i, successor(root, i));
        successor(root, i);
    printf("\n");
    delete_tree(root);
}

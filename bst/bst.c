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
    if (node != NULL) {
        delete_tree(node->left);
        delete_tree(node->right);
        free(node);
    }
}

int is_in_tree(struct Node* node, int i)
{
    if (node == NULL)
        return FALSE;
    else if (i < node->data)
        return is_in_tree(node->left, i);
    else if (i > node->data)
        return is_in_tree(node->right, i);
    else
        return TRUE;
}

int count(struct Node* node)
{
    if (node == NULL)
        return 0;
    return 1 + count(node->left) + count(node->right);
}

// height is 1 + max of children heights
int height(struct Node* node)
{
    if (node == NULL)
        return -1;
    int left = height(node->left);
    int right = height(node->right);
    return 1 + (left > right ? left : right);
}

int min(struct Node* node)
{
    if (node == NULL)
        exit(EXIT_FAILURE);
    while (node->left != NULL)
        node = node->left;
    return node->data;
}

int max(struct Node* node)
{
    if (node == NULL)
        exit(EXIT_FAILURE);
    while (node->right != NULL)
        node = node->right;
    return node->data;
}

struct Node * successor(struct Node* node, int i)
{
    /*  Use stack for in order traversal of tree.
        Once key is found, return the next largest.
        Return NULL if key not found or no successor. 
    */ 
    struct Node* succ = NULL;
    struct Stack* stack = new_stack(NULL);
    int found = FALSE;


    //  init stack with left most nodes
    while (!found && node != NULL) {
        if (node->data == i) {
            found = TRUE;
        } else {
            append_stack(stack, node);
            node = node->left;
        }
    }

    /*  node is currently NULL, so get next from stack,
        which is a min. Look at right child, children of  
        right child, and finally parent of this node (which
        is also from the stack) until key is found.
    */
    while (!found && stack->head != NULL) {
        node = pop_stack(stack);
        if (node != NULL) {
            node = node->right;
            if (node != NULL && node->data == i) {
                found = TRUE;
            } else while (!found && node != NULL) {
                if (node->data == i) {
                    found = TRUE;
                } else {
                    append_stack(stack, node);
                    node = node->left;
                }
            }
        }
    }

    /*  Once found, successor might be right child, left
        most child of right child, or parent of this node. */
    if (found) {
        succ = node->right;
        if (succ == NULL) {
            succ = pop_stack(stack);
        } else while (succ->left != NULL) {
            succ = succ->left;
        }
    }

    //  clean up and return value
    delete_stack(stack);
    return succ;
}

void print_in_order(struct Node* node)
{
    if (node->left != NULL)
        print_in_order(node->left);
    printf("%d ", node->data);
    if (node->right !=NULL)
        print_in_order(node->right);
}


#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

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
    if (node != NULL)
        stack->head = new_stack_node(node);
    else
        stack->head = NULL;
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
    free(stack);
}

void print_stack(struct Stack* stack)
{
    struct sNode* snode = stack->head;
    for ( ; snode != NULL; snode = snode->next)
        printf("%d ", snode->node->data);
}


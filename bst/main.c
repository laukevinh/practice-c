#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"

int main(void)
{
    test_new_node();
    test_insert();
    test_is_in_tree();
    test_count();
    test_height();
    test_min_max();
    test_successor();
    return 0;
}

void test_new_node(void)
{
    printf("Test new node\n");
    struct Node* root = new_node(0);
    assert(root->data == 0);
    delete_tree(root);
}

void test_insert(void)
{
    printf("Test insert\n");
    struct Node* root = new_node(10);
    insert(root, 5);
    insert(root, 15);
    insert(root, 7);
    assert(root->left->data == 5);
    assert(root->right->data == 15);
    assert(root->left->right->data == 7);
    delete_tree(root);
}

void test_is_in_tree(void)
{
    printf("Test is in tree\n");
    struct Node* root = new_node(10);
    for (int i=0; i<20; i+=4)
        insert(root, i);
    assert(is_in_tree(root, 0) == 1);
    assert(is_in_tree(root, 2) == 0);
    assert(is_in_tree(root, 20) == 0);
    assert(is_in_tree(root, 10) == 1);
    delete_tree(root);
}

void test_count(void)
{
    printf("Test count\n");
    struct Node* root = new_node(10);
    for (int i=0; i<20; i+=4)
        insert(root, i);
    assert(count(root) == 6);
    insert(root, 2);
    assert(count(root) == 7);
    insert(root, 2);
    assert(count(root) == 7);
    delete_tree(root);
}

void test_height(void)
{
    printf("Test height\n");
    struct Node* root = new_node(10);
    assert(height(root) == 0);
    for (int i=0; i<20; i+=4)
        insert(root, i);
    assert(height(root) == 3);
    delete_tree(root);
}

void test_min_max(void)
{
    printf("Test min and max\n");
    struct Node* root = new_node(10);
    for (int i=-4; i<20; i+=4)
        insert(root, i);
    assert(min(root) == -4);
    assert(max(root) == 16);
    delete_tree(root);
}

void test_successor(void)
{
    struct Node* root = new_node(8);
    printf("Test successor\n");
    int a[5] = { 6, 16, 5, 7, 10 };
    for (int i=0; i<5; i++)
        insert(root, a[i]);
    assert(successor(root, 6)->data == 7);
    assert(successor(root, 7)->data == 8);
    assert(successor(root, 8)->data == 10);
    delete_tree(root);

    root = new_node(50);
    int b[14] = { 40, 80, 30, 45, 60, 55, 51, 54, 53, 52, 59, 58, 57, 56 };
    for (int i=0; i<14; i++)
        insert(root, b[i]);
    assert(successor(root, 30)->data == 40);
    assert(successor(root, 40)->data == 45);
    assert(successor(root, 50)->data == 51);
    assert(successor(root, 51)->data == 52);
    assert(successor(root, 80) == NULL);
    delete_tree(root);

    root = new_node(0);
    for (int i=1; i<5; i++)
        insert(root, i);
    assert(successor(root, 0)->data == 1);
    delete_tree(root);

    assert(successor(NULL, 0) == NULL);
}

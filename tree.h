#ifndef C_TREE_H__
#define C_TREE_H__

#include <stdlib.h>
#include "list.h"

typedef struct {
    void *value;
    C_List *children;
} C_Tree_Node;

typedef struct {
    C_Tree_Node *root;
} C_Tree;

C_Tree *new_C_Tree() {
    C_Tree *p_tree = malloc(sizeof(C_Tree)); // allocate new tree
    C_Tree_Node *p_tree_root = malloc(sizeof(C_Tree_Node)); // allocate root node
    p_tree_root->children = new_C_List_Cap(0, 4); // create new list

    p_tree->root = p_tree_root; // assign root node
    return p_tree;
}

void C_Tree_Set_Root(C_Tree *p_tree, C_Tree_Node *p_node) {
    p_tree->root = p_node;
}

void C_Tree_Add_Child(C_Tree_Node *p_node, C_Tree_Node *p_child) {
    C_List_Push(p_node->children, p_child); // push child
}

#endif // C_TREE_H__
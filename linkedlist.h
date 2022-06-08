#ifndef LINKED_LIST_H__
#define LINKED_LIST_H__

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

struct C_Linked_List_Node;

typedef struct {
    void *value;
    struct C_Linked_List_Node *next;
} C_Linked_List_Node;

typedef struct {
    unsigned int size;
    C_Linked_List_Node *head;
    C_Linked_List_Node *last;
} C_Linked_List;

C_Linked_List *new_C_Linked_List() {
    C_Linked_List *p_l_list = malloc(sizeof(C_Linked_List)); // malloc list
    p_l_list->size = 0; // set size to 0
    return p_l_list;
}

C_Linked_List_Node *C_Linked_List_Get_Last(C_Linked_List *p_l_list) {
    return p_l_list->last;
}

C_Linked_List_Node *C_Linked_List_Get_Node(C_Linked_List *p_l_list, unsigned int index) {
    if(index >= p_l_list->size) index = (p_l_list->size - 1); // if index is greater: set to last element

    if(index == (p_l_list->size - 1)) return C_Linked_List_Get_Last(p_l_list); // return last if last is requested

    // Traverse Linked list
    C_Linked_List_Node *p_curr_node = p_l_list->head;
    for(int i = 0; i < index; i++) {
        p_curr_node = p_curr_node->next;
    }

    return p_curr_node;
}

unsigned int C_Linked_List_Size(C_Linked_List *p_list) {
    return p_list->size;
}

void *C_Linked_List_Get(C_Linked_List *p_l_list, unsigned int index) {
    return C_Linked_List_Get_Node(p_l_list, index)->value;
}

void C_Linked_List_Push(C_Linked_List *p_l_list, void *p_elem) {
    C_Linked_List_Node *p_l_list_node = malloc(sizeof(C_Linked_List_Node));
    p_l_list_node->value = p_elem;

    if(p_l_list->size == 0) {
        // List is not initalized
        p_l_list->head = p_l_list_node; // Set head to node
    } else {
        C_Linked_List_Get_Node(p_l_list, p_l_list->size)->next = p_l_list_node;
    }

    p_l_list->last = p_l_list_node; // set last
    p_l_list->size++;
}

void C_Linked_List_Remove(C_Linked_List *p_l_list, unsigned int index) {
    if(index >= p_l_list->size) return;

    C_Linked_List_Node *p_before_node = C_Linked_List_Get_Node(p_l_list, index - 1);
    C_Linked_List_Node *p_curr_node = C_Linked_List_Get_Node(p_l_list, index);
    C_Linked_List_Node *p_next_node = C_Linked_List_Get_Node(p_l_list, index + 1);

    if(index == (p_l_list->size - 1)) {
        // Remove Last element
        p_next_node = NULL; // Set Next node to NULL
    }

    // set beforeNode->next = nextNode
    p_before_node->next = p_next_node;

    free(p_curr_node); // free current node

    p_l_list->size--; // decrement size
}

void C_Linked_List_Insert(C_Linked_List *p_l_list, void *p_elem, unsigned int index) {
    if(index >= p_l_list->size) return;

    C_Linked_List_Node *p_curr_node = C_Linked_List_Get_Node(p_l_list, index);
    C_Linked_List_Node *p_before_node = C_Linked_List_Get_Node(p_l_list, index - 1); // node before current index
    
    // create new node
    C_Linked_List_Node *p_new_node = malloc(sizeof(C_Linked_List_Node));
    p_new_node->value = p_elem;
    // set beforeNode->next = newNode
    p_before_node->next = p_new_node;
    // set newNode->next = currNode
    p_new_node->next = p_curr_node;
    
    p_l_list->size++; // increment size by one
}

C_List *C_Linked_List_To_List(C_Linked_List *p_l_list) {
    C_List *p_ls = new_C_List(p_l_list->size); // create new c_list
    // Traverse Linked list
    C_Linked_List_Node *p_curr_node = p_l_list->head;
    for(int i = 0; i < p_l_list->size; i++) {
        C_List_Replace(p_ls, i, p_curr_node->value);
        p_curr_node = p_curr_node->next;
    }
    return p_ls;
}

#endif // LINKED_LIST_H__
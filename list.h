#ifndef VECTOR_H__
#define VECTOR_H__

#include <stdlib.h>

typedef struct {
    unsigned int size;
    unsigned int capacity;
    void **elements;
} C_List;

#define C_List_DEFAULT_CAPACITY 16

C_List *new_C_List(unsigned int size) {
    C_List *p_ls = malloc(sizeof(C_List));
    p_ls->size = size;
    p_ls->capacity = size * 2;
    p_ls->elements = malloc(sizeof(void *) * size * 2);
    return p_ls;
}

C_List *new_C_List_Cap(unsigned int size, unsigned int capacity) {
    C_List *p_ls = malloc(sizeof(C_List));
    p_ls->size = size;
    p_ls->capacity = capacity;
    p_ls->elements = malloc(sizeof(void *) * size * 2);
    return p_ls;
}

unsigned int C_List_Length(C_List *p_ls) {
    return p_ls->size;
}

unsigned int C_List_Capacity(C_List *p_ls) {
    return p_ls->capacity;
}

void C_List_Push(C_List *p_ls, void *p_elem) {
    /* Check for capacity */
    if(p_ls->size >= p_ls->capacity) {
        /* Resize Vector */
        p_ls->elements = realloc(p_ls->elements, sizeof(void *) * p_ls->capacity * 2);
        p_ls->capacity *= 2;
    }
    p_ls->elements[p_ls->size] = p_elem; // Add Element to last place
    p_ls->size++; // increment size
}

void C_List_Pop(C_List *p_ls) {
    p_ls->size--; // decrement size
    p_ls->elements[p_ls->size] = NULL; // set element to NULL
}

void C_List_Remove_Back(C_List *p_ls, unsigned int count) {
    p_ls->size -= count; // remove last elements
}

void C_List_Remove_Front(C_List *p_ls, unsigned int count) {
    void **p_temp_elems = malloc(sizeof(void *) * p_ls->capacity);
    if(count > p_ls->size) { // check if count is greater than size
        count = p_ls->size; // set count to size
    }
    for(int i = count; i < p_ls->capacity; i++) {
        p_temp_elems[i - count] = p_ls->elements[i]; // set element of temp list to corresponding element from list
    }
    free(p_ls->elements); // free old elements
    p_ls->elements = p_temp_elems; // set new elements
}

void *C_List_Get(C_List *p_ls, unsigned int index) {
    if(index >= p_ls->size) return NULL; // return null if invalid index
    return p_ls->elements[index]; // return element at index
}

void *C_List_Head(C_List *p_ls) {
    return C_List_Get(p_ls, 0);
}

void **C_List_Tail(C_List *p_ls) {
    void **p_temp_elements = malloc(sizeof(void *) * (p_ls->size - 1)); // allocate new list, length = len(p_ls) - 1
    // put all elements in list except first one
    for(int i = 1; i < p_ls->size; i++) {
        p_temp_elements[i-1] = p_ls->elements[i];
    }
    return p_temp_elements;
}

void C_List_Replace(C_List *p_ls, unsigned int index, void *p_elem) {
    p_ls->elements[index] = p_elem; // set element at index
}

#endif // VECTOR_H__
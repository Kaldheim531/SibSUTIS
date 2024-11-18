#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define NEG_INFINITY -1 // Используем другое имя для "минус бесконечности"

struct fibheap {
    int key;
    char *value;
    int degree;
    bool mark;
    struct fibheap *parent;
    struct fibheap *child;
    struct fibheap *left;
    struct fibheap *right;
    struct fibheap *min;
    int nnodes;
};

struct fibheap* allocate_memory();
void free_memory(struct fibheap *node);
void fibheap_add_node_to_root_list(struct fibheap *node, struct fibheap *h);
struct fibheap* fibheap_insert(struct fibheap *heap, int key, char *value);
struct fibheap* fibheap_min(struct fibheap *heap);
void fibheap_link_lists(struct fibheap *heap1, struct fibheap *heap2);
struct fibheap* fibheap_union(struct fibheap *heap1, struct fibheap *heap2);
void fibheap_remove_node_from_root_list(struct fibheap *node, struct fibheap *heap);
struct fibheap* fibheap_delete_min(struct fibheap *heap);
void fibheap_consolidate(struct fibheap *heap);
int D(int n);
void fibheap_link(struct fibheap *heap, struct fibheap *y, struct fibheap *x);
void fibheap_decrease_key(struct fibheap *heap, struct fibheap *x, int newkey);
void fibheap_cut(struct fibheap *heap, struct fibheap *x, struct fibheap *y);
void fibheap_cascading_cut(struct fibheap *heap, struct fibheap *y);
void fibheap_delete(struct fibheap *heap, struct fibheap *x);



/*
struct fibheap *fibheap_insert(struct fibheap *heap, int key, char *value)
struct fibheap *fibheap_min(struct fibheap *heap)
struct fibheap *fibheap_union(struct fibheap *heap1, struct fibheap *heap2)
struct fibheap *fibheap_delete_min(struct fibheap *heap)
struct fibheap *fibheap_decrease_key(struct fibheap *heap, struct fibheap *node, int newkey)
struct fibheap *fibheap_delete(struct fibheap *heap, int key)*/
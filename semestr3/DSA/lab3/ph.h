#ifndef PH_H
#define PH_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// Структура для узла фибоначчиевой кучи
struct fibheap {
    int key;
    char *value;
    int degree;
    bool mark;
    struct fibheap *parent;
    struct fibheap *child;
    struct fibheap *left;
    struct fibheap *right;
};

// Структура для фибоначчиевой кучи
struct FibHeap {
    struct fibheap *min;
    int nnodes;
};

// Прототипы функций
struct FibHeap *fibheap_insert(struct FibHeap *heap, int key, char *value);
struct fibheap *fibheap_min(struct FibHeap *heap);
struct FibHeap *fibheap_union(struct FibHeap *heap1, struct FibHeap *heap2);
struct fibheap *fibheap_delete_min(struct FibHeap *heap);
struct FibHeap *fibheap_decrease_key(struct FibHeap *heap, struct fibheap *node, int newkey);
struct FibHeap *fibheap_delete(struct FibHeap *heap, int key);
void fibheap_free(struct FibHeap *heap);

#endif // PH_H
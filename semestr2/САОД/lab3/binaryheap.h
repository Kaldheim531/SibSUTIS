#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>

struct heap_node
{
    int vertex;
    int priority;
};

struct binary_heap
{
    struct heap_node *array;
    int capacity;
    int size;
};

struct binary_heap *create_heap(int capacity);
void swap(struct heap_node *x, struct heap_node *y);
void heapify_up(struct binary_heap *heap, int index);
void heapify_down(struct binary_heap *heap, int index);
void insert(struct binary_heap *heap, int vertex, int priority);
int extract_min(struct binary_heap *heap);
int contains(struct binary_heap *heap, int vertex);
void decrease_priority(struct binary_heap *heap, int vertex, int new_priority);
void destroy_heap(struct binary_heap *heap);
int is_empty(struct binary_heap *heap);
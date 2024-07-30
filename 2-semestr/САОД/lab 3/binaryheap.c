#include "graph.h"
#include "queue_array.h"
#include "binaryheap.h"

struct binary_heap *create_heap(int capacity)
{
    struct binary_heap *heap = (struct binary_heap *)malloc(sizeof(struct binary_heap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->array = (struct heap_node *)malloc(capacity * sizeof(struct heap_node));
    return heap;
}

void swap(struct heap_node *x, struct heap_node *y)
{
    struct heap_node temp = *x;
    *x = *y;
    *y = temp;
}

void heapify_up(struct binary_heap *heap, int index)
{
    int parent = (index - 1) / 2;
    while (index > 0 && heap->array[parent].priority > heap->array[index].priority)
    {
        swap(&heap->array[parent], &heap->array[index]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void heapify_down(struct binary_heap *heap, int index)
{
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < heap->size && heap->array[left].priority < heap->array[smallest].priority)
    {
        smallest = left;
    }

    if (right < heap->size && heap->array[right].priority < heap->array[smallest].priority)
    {
        smallest = right;
    }

    if (smallest != index)
    {
        swap(&heap->array[index], &heap->array[smallest]);
        heapify_down(heap, smallest);
    }
}

void insert(struct binary_heap *heap, int vertex, int priority)
{
    if (heap->size == heap->capacity)
    {
        printf("Heap is full. Cannot insert more elements.\n");
        return;
    }

    heap->size++;
    int index = heap->size - 1;
    heap->array[index].vertex = vertex;
    heap->array[index].priority = priority;
    heapify_up(heap, index);
}

int extract_min(struct binary_heap *heap)
{
    if (heap->size == 0)
    {
        printf("Heap is empty.\n");
        return -1;
    }

    int min_vertex = heap->array[0].vertex;
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);
    return min_vertex;
}

int contains(struct binary_heap *heap, int vertex)
{
    for (int i = 0; i < heap->size; i++)
    {
        if (heap->array[i].vertex == vertex)
        {
            return 1;
        }
    }
    return 0;
}

void decrease_priority(struct binary_heap *heap, int vertex, int new_priority)
{
    int index;
    for (int i = 0; i < heap->size; i++)
    {
        if (heap->array[i].vertex == vertex)
        {
            index = i;
            break;
        }
    }

    if (new_priority < heap->array[index].priority)
    {
        heap->array[index].priority = new_priority;
        heapify_up(heap, index);
    }
}

void destroy_heap(struct binary_heap *heap)
{
    free(heap->array);
    free(heap);
}

int is_empty(struct binary_heap *heap)
{
    return heap->size == 0;
}

#include "ph.h"

int main() {
    struct fibheap *heap = allocate_memory();
    heap->min = NULL;
    heap->nnodes = 0;

    // Вставка элементов в кучу
    heap = fibheap_insert(heap, 3, "three");
    heap = fibheap_insert(heap, 7, "seven");
    heap = fibheap_insert(heap, 1, "one");
    heap = fibheap_insert(heap, 4, "four");
    heap = fibheap_insert(heap, 2, "two");

    // Вывод минимального элемента
    struct fibheap *min_node = fibheap_min(heap);
    if (min_node != NULL) {
        printf("Minimum key: %d, value: %s\n", min_node->key, min_node->value);
    } else {
        printf("Heap is empty.\n");
    }

    // Удаление минимального элемента
    struct fibheap *deleted_min = fibheap_delete_min(heap);
    if (deleted_min != NULL) {
        printf("Deleted minimum key: %d, value: %s\n", deleted_min->key, deleted_min->value);
        free_memory(deleted_min);
    } else {
        printf("Heap is empty.\n");
    }

    // Вывод нового минимального элемента
    min_node = fibheap_min(heap);
    if (min_node != NULL) {
        printf("New minimum key: %d, value: %s\n", min_node->key, min_node->value);
    } else {
        printf("Heap is empty.\n");
    }

    // Уменьшение ключа элемента
    struct fibheap *node_to_decrease = heap->min->right; // Предположим, что это элемент с ключом 4
    fibheap_decrease_key(heap, node_to_decrease, 0);
    printf("Decreased key of node with value 'four' to 0.\n");

    // Вывод нового минимального элемента
    min_node = fibheap_min(heap);
    if (min_node != NULL) {
        printf("New minimum key: %d, value: %s\n", min_node->key, min_node->value);
    } else {
        printf("Heap is empty.\n");
    }

    // Удаление элемента
    fibheap_delete(heap, node_to_decrease);
    printf("Deleted node with value 'four'.\n");

    // Вывод нового минимального элемента
    min_node = fibheap_min(heap);
    if (min_node != NULL) {
        printf("New minimum key: %d, value: %s\n", min_node->key, min_node->value);
    } else {
        printf("Heap is empty.\n");
    }

    // Освобождение памяти
    while (heap->min != NULL) {
        struct fibheap *temp = fibheap_delete_min(heap);
        free_memory(temp);
    }
    free_memory(heap);

    return 0;
}
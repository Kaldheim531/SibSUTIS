#include "ph.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    struct FibHeap *heap = (struct FibHeap *)malloc(sizeof(struct FibHeap));
    heap->min = NULL;
    heap->nnodes = 0;

    // Вставка элементов
    heap = fibheap_insert(heap, 3, "three");
    heap = fibheap_insert(heap, 1, "one");
    heap = fibheap_insert(heap, 4, "four");
    heap = fibheap_insert(heap, 2, "two");

    // Вывод минимального элемента
    struct fibheap *min_node = fibheap_min(heap);
    printf("Min key: %d, Min value: %s\n", min_node->key, min_node->value);

    // Удаление минимального элемента
    fibheap_delete_min(heap);
    min_node = fibheap_min(heap);
    printf("Min key after delete: %d, Min value: %s\n", min_node->key, min_node->value);

    // Уменьшение ключа
    fibheap_decrease_key(heap, heap->min->right, 0);
    min_node = fibheap_min(heap);
    printf("Min key after decrease: %d, Min value: %s\n", min_node->key, min_node->value);

    // Удаление узла по ключу
    heap = fibheap_delete(heap, 3);
    min_node = fibheap_min(heap);
    printf("Min key after delete by key: %d, Min value: %s\n", min_node->key, min_node->value);

    // Создание второй кучи
    struct FibHeap *heap2 = (struct FibHeap *)malloc(sizeof(struct FibHeap));
    heap2->min = NULL;
    heap2->nnodes = 0;

    // Вставка элементов во вторую кучу
    heap2 = fibheap_insert(heap2, 7, "seven");
    heap2 = fibheap_insert(heap2, 5, "five");
    heap2 = fibheap_insert(heap2, 6, "six");

    // Объединение двух куч
    heap = fibheap_union(heap, heap2);
    min_node = fibheap_min(heap);
    printf("Min key after union: %d, Min value: %s\n", min_node->key, min_node->value);

    // Освобождение памяти
    fibheap_free(heap);

    return 0;
}
#include "ph.h"


// Вспомогательная функция для выделения памяти под узел
struct fibheap *allocate_node() {
    struct fibheap *node = (struct fibheap *)malloc(sizeof(struct fibheap));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    return node;
}

// Вспомогательная функция для освобождения памяти
void free_node(struct fibheap *node) {
    free(node);
}

// Функция для добавления узла в список корней
void fibheap_add_node_to_root_list(struct fibheap *node, struct fibheap *h) {
    if (h == NULL) return;

    if (h->left == h) { // Список h содержит один корень
        h->left = node;
        h->right = node;
        node->right = h;
        node->left = h;
    } else { // Список h содержит более одного корня
        struct fibheap *lnode = h->left;
        h->left = node;
        node->right = h;
        node->left = lnode;
        lnode->right = node;
    }
}

// Функция для удаления узла из списка корней
void fibheap_remove_node_from_root_list(struct fibheap *node, struct FibHeap *heap) {
    if (node->left == node) {
        heap->min = NULL;
    } else {
        node->left->right = node->right;
        node->right->left = node->left;
        if (heap->min == node) {
            heap->min = node->right;
        }
    }
}

// Функция для объединения двух списков корней
void fibheap_link_lists(struct fibheap *heap1, struct fibheap *heap2) {
    if (heap1 == NULL || heap2 == NULL) return;

    struct fibheap *left1 = heap1->left;
    struct fibheap *left2 = heap2->left;
    left1->right = heap2;
    heap2->left = left1;
    heap1->left = left2;
    left2->right = heap1;
}

// Функция для обмена двух узлов
void fibheap_swap(struct fibheap *x, struct fibheap *y) {
    struct fibheap *temp = x;
    x = y;
    y = temp;
}

// Функция для связывания двух узлов
void fibheap_link(struct FibHeap *heap, struct fibheap *y, struct fibheap *x) {
    /* Делаем y дочерним узлом x */
    fibheap_remove_node_from_root_list(y, heap);
    
    y->parent = x;
    if (x->child == NULL) {
        x->child = y;
        y->left = y;
        y->right = y;
    } else {
        fibheap_add_node_to_root_list(y, x->child);
    }
    x->degree++;
    y->mark = false;
}

// Функция для вставки узла в кучу
struct FibHeap *fibheap_insert(struct FibHeap *heap, int key, char *value) {
    struct fibheap *node = allocate_node();
    node->key = key;
    node->value = value;
    node->degree = 0;
    node->mark = false;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;

    if (heap->min == NULL || node->key < heap->min->key) {
        heap->min = node;
    }

    fibheap_add_node_to_root_list(node, heap->min);
    heap->nnodes++;
    return heap;
}

// Функция для получения минимального узла
struct fibheap *fibheap_min(struct FibHeap *heap) {
    return heap->min;
}

// Функция для объединения двух куч
struct FibHeap *fibheap_union(struct FibHeap *heap1, struct FibHeap *heap2) {
    struct FibHeap *heap = (struct FibHeap *)malloc(sizeof(struct FibHeap));
    heap->min = heap1->min;
    fibheap_link_lists(heap1->min, heap2->min);

    if (heap1->min == NULL || (heap2->min != NULL && heap2->min->key < heap->min->key)) {
        heap->min = heap2->min;
    }

    heap->nnodes = heap1->nnodes + heap2->nnodes;
    free(heap1);
    free(heap2);
    return heap;
}

// Функция для удаления минимального узла
struct fibheap *fibheap_delete_min(struct FibHeap *heap) {
    struct fibheap *z = heap->min;
    if (z == NULL) return NULL;

    struct fibheap *x = z->child;
    if (x != NULL) {
        do {
            struct fibheap *next = x->right;
            fibheap_add_node_to_root_list(x, heap->min); /* Добавляем дочерний узел x в список корней */
            x->parent = NULL;
            x = next;
        } while (x != z->child);
    }

    fibheap_remove_node_from_root_list(z, heap); /* Удаляем z из списка корней */

    if (z == z->right) {
        heap->min = NULL;
    } else {
        heap->min = z->right;
        fibheap_consolidate(heap);
    }

    heap->nnodes--;
    return z;
}

// Функция для консолидации кучи
void fibheap_consolidate(struct FibHeap *heap) {
    int max_degree = (int)log2(heap->nnodes) + 1;
    struct fibheap **A = (struct fibheap **)calloc(max_degree, sizeof(struct fibheap *));

    struct fibheap *w = heap->min;
    if (w != NULL) {
        struct fibheap *next = w;
        do {
            struct fibheap *x = next; /* Цикл по всем узлам списка корней */
            next = next->right;
            int d = x->degree;
            while (A[d] != NULL) {
            next = next->right;
                struct fibheap *y = A[d]; /* Степень y совпадает со степенью x */
                if (x->key > y->key) {
                    fibheap_swap(x, y); /* Обмениваем x и y */
                }
                fibheap_link(heap, y, x);
                A[d] = NULL;
                d++;
            }
            A[d] = x;
        } while (next != w);
    }
    
    heap->min = NULL; /*Находим минимальный узел */
    for (int i = 0; i < max_degree; i++) {
        if (A[i] != NULL) {
            fibheap_add_node_to_root_list(A[i], heap->min); /* Добавляем A[i] в список корней */
            if (heap->min == NULL || A[i]->key < heap->min->key) {
                heap->min = A[i];
            }
        }
    }

    free(A);
}

// Функция для уменьшения ключа узла
struct FibHeap *fibheap_decrease_key(struct FibHeap *heap, struct fibheap *node, int newkey) {
    if (newkey > node->key) {
        return heap; // Новый ключ больше текущего значения ключа
    }

    node->key = newkey;
    struct fibheap *y = node->parent;
    if (y != NULL && node->key < y->key) {
        /* Нарушены свойства min-heap: ключ родителя больше */
        /* Вырезаем x и переносим его в список корней */
        fibheap_cut(heap, node, y);
        fibheap_cascading_cut(heap, y);
    }
    /* Корректируем указатель на минимальный узел */
    if (node->key < heap->min->key) {
        heap->min = node;
    }

    return heap;
}

// Функция для вырезания узла
void fibheap_cut(struct FibHeap *heap, struct fibheap *x, struct fibheap *y) {
    fibheap_remove_node_from_root_list(x, y);
    y->degree--;
    fibheap_add_node_to_root_list(x, heap->min);
    x->parent = NULL;
    x->mark = false;
}

// Функция для каскадного вырезания
void fibheap_cascading_cut(struct FibHeap *heap, struct fibheap *y) {
    struct fibheap *z = y->parent;
    if (z != NULL) {
        if (y->mark == false) {
            y->mark = true;
        } else {
            fibheap_cut(heap, y, z);
            fibheap_cascading_cut(heap, z);
        }
    }
}

// Функция для удаления узла по ключу
struct FibHeap *fibheap_delete(struct FibHeap *heap, int key) {
    struct fibheap *node = heap->min;
    while (node != NULL) {
        if (node->key == key) {
            fibheap_decrease_key(heap, node, -1); // Устанавливаем ключ в -1 (минимально возможное значение)
            fibheap_delete_min(heap);
            break;
        }
        node = node->right;
        if (node == heap->min) break;
    }
    return heap;
}

// Функция для освобождения всех узлов кучи
void fibheap_free_nodes(struct fibheap *node) {
    if (node == NULL) return;

    struct fibheap *current = node;
    do {
        struct fibheap *next = current->right;
        fibheap_free_nodes(current->child);
        free(current);
        current = next;
    } while (current != node);
}

// Функция для освобождения всей кучи
void fibheap_free(struct FibHeap *heap) {
    if (heap == NULL) return;

    fibheap_free_nodes(heap->min);
    free(heap);
}
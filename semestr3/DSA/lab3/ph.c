

#include "ph.h"


struct fibheap* allocate_memory() {
    struct fibheap *node = (struct fibheap*)malloc(sizeof(struct fibheap));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    // Инициализация полей структуры
    node->key = 0;
    node->value = NULL;
    node->degree = 0;
    node->mark = false;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    node->min = NULL;
    node->nnodes = 0;
    return node;
}

void free_memory(struct fibheap *node) {
    free(node);
}

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

struct fibheap* fibheap_insert(struct fibheap *heap, int key, char *value) {
    struct fibheap *node = allocate_memory();
    node->key = key;
    node->value = value;
    node->degree = 0;
    node->mark = false;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;

    // Добавляем узел в список корней heap
    fibheap_add_node_to_root_list(node, heap->min);

    if (heap->min == NULL || node->key < heap->min->key) {
        heap->min = node;
    }

    heap->nnodes++;
    return heap;
}

struct fibheap* fibheap_min(struct fibheap *heap) {
    return heap->min;
}

void fibheap_link_lists(struct fibheap *heap1, struct fibheap *heap2) {
    if (heap1 == NULL || heap2 == NULL) return;

    struct fibheap *left1 = heap1->left;
    struct fibheap *left2 = heap2->left;

    left1->right = heap2;
    heap2->left = left1;
    heap1->left = left2;
    left2->right = heap1;
}

struct fibheap* fibheap_union(struct fibheap *heap1, struct fibheap *heap2) {
    struct fibheap *heap = allocate_memory();
    heap->min = heap1->min;
    fibheap_link_lists(heap1->min, heap2->min);

    if (heap1->min == NULL || (heap2->min != NULL && heap2->min->key < heap->min->key)) {
        heap->min = heap2->min;
    }

    heap->nnodes = heap1->nnodes + heap2->nnodes;
    free_memory(heap1);
    free_memory(heap2);
    return heap;
}

void fibheap_remove_node_from_root_list(struct fibheap *node, struct fibheap *heap) {
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

struct fibheap* fibheap_delete_min(struct fibheap *heap) {
    struct fibheap *z = heap->min;
    if (z == NULL) return NULL;

    // Добавляем все дочерние узлы z в список корней
    struct fibheap *x = z->child;
    if (x != NULL) {
        do {
            struct fibheap *next = x->right;
            fibheap_add_node_to_root_list(x, heap);
            x->parent = NULL;
            x = next;
        } while (x != z->child);
    }

    // Удаляем z из списка корней
    fibheap_remove_node_from_root_list(z, heap);

    if (z == z->right) {
        heap->min = NULL;
    } else {
        heap->min = z->right;
        fibheap_consolidate(heap);
    }

    heap->nnodes--;
    return z;
}

int D(int n) {
    return (int)floor(log2(n));
}

void fibheap_consolidate(struct fibheap *heap) {
    int max_degree = D(heap->nnodes) + 1;
    struct fibheap **A = (struct fibheap**)calloc(max_degree, sizeof(struct fibheap*));

    struct fibheap *w = heap->min;
    if (w != NULL) {
        struct fibheap *next = w;
        do {
            struct fibheap *x = w;
            int d = x->degree;
            while (A[d] != NULL) {
                struct fibheap *y = A[d];
                if (x->key > y->key) {
                    struct fibheap *temp = x;
                    x = y;
                    y = temp;
                }
                fibheap_link(heap, y, x);
                A[d] = NULL;
                d++;
            }
            A[d] = x;
            w = w->right;
        } while (w != next);
    }

    heap->min = NULL;
    for (int i = 0; i < max_degree; i++) {
        if (A[i] != NULL) {
            fibheap_add_node_to_root_list(A[i], heap);
            if (heap->min == NULL || A[i]->key < heap->min->key) {
                heap->min = A[i];
            }
        }
    }

    free(A);
}

void fibheap_link(struct fibheap *heap, struct fibheap *y, struct fibheap *x) {
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

void fibheap_decrease_key(struct fibheap *heap, struct fibheap *x, int newkey) {
    if (newkey > x->key) {
        return; // Новый ключ больше текущего значения ключа
    }

    x->key = newkey;
    struct fibheap *y = x->parent;
    if (y != NULL && x->key < y->key) {
        fibheap_cut(heap, x, y);
        fibheap_cascading_cut(heap, y);
    }

    if (x->key < heap->min->key) {
        heap->min = x;
    }
}

void fibheap_cut(struct fibheap *heap, struct fibheap *x, struct fibheap *y) {
    // Удаляем x из списка дочерних узлов y
    if (x->left == x) {
        y->child = NULL;
    } else {
        x->left->right = x->right;
        x->right->left = x->left;
        if (y->child == x) {
            y->child = x->right;
        }
    }
    y->degree--;

    // Добавляем x в список корней кучи heap
    fibheap_add_node_to_root_list(x, heap);
    x->parent = NULL;
    x->mark = false;
}

void fibheap_cascading_cut(struct fibheap *heap, struct fibheap *y) {
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

void fibheap_delete(struct fibheap *heap, struct fibheap *x) {
    fibheap_decrease_key(heap, x, NEG_INFINITY);
    fibheap_delete_min(heap);
}

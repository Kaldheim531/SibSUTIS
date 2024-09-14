#include "rbtrees.h"

rbtree *CreateNode(int key, char *value) {
    rbtree *node = (rbtree *)malloc(sizeof(rbtree));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    node->key = key;
    node->value = strdup(value);
    node->color = RED;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

rbtree *rbtree_add(rbtree *root, int key, char *value) {
    rbtree *tree = root;
    rbtree *parent = NULL;

    while (tree != NULL) {
        parent = tree;
        if (key < tree->key) {
            tree = tree->left;
        } else if (key > tree->key) {
            tree = tree->right;
        } else {
            // Ключ уже присутствует в дереве
            return root;
        }
    }

    rbtree *node = CreateNode(key, value);
    node->parent = parent;

    if (parent == NULL) {
        // Пустое дерево
        root = node;
    } else if (key < parent->key) {
        parent->left = node;
    } else {
        parent->right = node;
    }

    RBTree_Add_Fixup(root, node);
    return root;
}
    
void RBTree_Add_Fixup(rbtree *root, rbtree *node) {
    while (node != root && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            rbtree *uncle = node->parent->parent->right;
            if (uncle != NULL && uncle->color == RED) {
                // Случай 1: дядя красный
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    // Случай 2: дядя черный, узел - правый потомок
                    node = node->parent;
                    root = rotate_left(root, node);
                }
                // Случай 3: дядя черный, узел - левый потомок
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                root = rotate_right(root, node->parent->parent);
            }
        } else {
            rbtree *uncle = node->parent->parent->left;
            if (uncle != NULL && uncle->color == RED) {
                // Случай 1: дядя красный
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    // Случай 2: дядя черный, узел - левый потомок
                    node = node->parent;
                    root = rotate_right(root, node);
                }
                // Случай 3: дядя черный, узел - правый потомок
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                root = rotate_left(root, node->parent->parent);
            }
        }
    }
    root->color
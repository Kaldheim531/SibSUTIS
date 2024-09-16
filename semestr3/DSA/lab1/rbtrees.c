#include "rbtrees.h"

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}


struct rbtree* CreateNode(int key, char *value) {
    struct rbtree *node = (struct rbtree*)malloc(sizeof(struct rbtree));
    if (node == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
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

void leftRotate(struct rbtree **root, struct rbtree *x) {
    struct rbtree *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void rightRotate(struct rbtree **root, struct rbtree *x) {
    struct rbtree *y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
}

void RBTree_Add_Fixup(struct rbtree **root, struct rbtree *z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            struct rbtree *y = z->parent->parent->right; // Uncle
            if (y != NULL && y->color == RED) {
                // Case 1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    // Case 2 --> Case 3
                    z = z->parent;
                    leftRotate(root, z);
                }
                // Case 3
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            struct rbtree *y = z->parent->parent->left; // Uncle
            if (y != NULL && y->color == RED) {
                // Case 1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    // Case 2 --> Case 3
                    z = z->parent;
                    rightRotate(root, z);
                }
                // Case 3
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}


struct rbtree *rbtree_add(struct rbtree *root, int key, char *value) {
    struct rbtree *tree = root;
    struct rbtree *parent = NULL;

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

   struct rbtree *node = CreateNode(key, value); 
    
   if (parent == NULL) {
        // Пустое дерево
        root = node;
    } else if (key < parent->key) {
        parent->left = node;
    } else {
        parent->right = node;
    }
    node->parent = parent;

    RBTree_Add_Fixup(&root, node);
    return root;
}

void rbtree_print_dfs(struct rbtree *root, int level) {
    if (root == NULL) return;
    rbtree_print_dfs(root->right, level + 1);
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("%d (%s)\n", root->key, root->color == RED ? "RED" : "BLACK");
    rbtree_print_dfs(root->left, level + 1);
}
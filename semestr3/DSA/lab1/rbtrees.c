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

struct rbtree *rbtree_lookup(struct rbtree *root, int key) {
    while (root != NULL && key != root->key) {
        if (key < root->key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root;
}

struct rbtree *rbtree_min(struct rbtree *root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

struct rbtree *rbtree_max(struct rbtree *root) {
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

void rbtree_transplant(struct rbtree **root, struct rbtree *u, struct rbtree *v) {
    if (u->parent == NULL) {
        *root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}

void rbtree_delete_fixup(struct rbtree **root, struct rbtree *x) {
    while (x != *root && x->color == BLACK) {
        if (x == x->parent->left) {
            struct rbtree *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            struct rbtree *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = BLACK;
}

struct rbtree *rbtree_delete(struct rbtree *root, int key) {
    struct rbtree *z = rbtree_lookup(root, key);
    if (z == NULL) {
        return root; // Узел с ключом key не найден
    }

    struct rbtree *y = z;
    struct rbtree *x;
    Color y_original_color = y->color;

    if (z->left == NULL) {
        x = z->right;
        rbtree_transplant(&root, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        rbtree_transplant(&root, z, z->left);
    } else {
        y = rbtree_min(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != NULL) {
                x->parent = y;
            }
        } else {
            rbtree_transplant(&root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbtree_transplant(&root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_original_color == BLACK) {
        rbtree_delete_fixup(&root, x);
    }

    free(z->value);
    free(z);
    return root;
}
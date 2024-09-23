#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define nil NULL
typedef enum { RED, BLACK } Color;

struct rbtree {
    int key;
    char *value;
    Color color;
    struct rbtree *left;
    struct rbtree *right;
    struct rbtree *parent;
};

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
                z = z->parent->parent; /*Так как красный узел 𝑔 может иметь красного родителя, делаем его
текущим узлом и продвигаемся вверх по дереву*/
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
        if (x == x->parent->left) { /*Дважды черная вершина 𝑥 является левым потомком свое-
го родителя 𝑥.𝑝𝑎𝑟𝑒𝑛𝑡 черного цвета и имеет красный родственный узел 𝑤.*/
            struct rbtree *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                /*Узел 𝑤 имеет черный цвет, оба его потомка также черные.*/
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    /*Узел 𝑤 имеет черный цвет, 
                    его левый потомок – красный,
                    а правый – черный */
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                /*Узел 𝑤 имеет черный цвет, 
                его правый потомок – красный.*/
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

int black_height(struct rbtree *node) {
    if (node == NULL) {
        return 1; // Пустые узлы считаются черными
    }
    int left_height = black_height(node->left);
    int right_height = black_height(node->right);
    if (left_height != right_height) {
        return -1; // Если высоты не совпадают, дерево некорректно
    }
    return left_height + (node->color == BLACK ? 1 : 0);
}

int check_black_height(struct rbtree *node) {
    if (node == NULL) return 1; // NIL-узел считается черным

    int left_black_height = check_black_height(node->left);
    int right_black_height = check_black_height(node->right);

    if (left_black_height != right_black_height) {
        printf("Ошибка: разная черная высота в левом и правом поддеревьях узла с ключом %d\n", node->key);
        return -1; // Ошибка
    }

    return left_black_height + (node->color == BLACK ? 1 : 0);
}

void check_red_properties(struct rbtree *node) {
    if (node == NULL) return;

    if (node->color == RED) {
        if (node->left != NULL && node->left->color == RED) {
            printf("Ошибка: два красных узла подряд (левый потомок).\n");
        }
        if (node->right != NULL && node->right->color == RED) {
            printf("Ошибка: два красных узла подряд (правый потомок).\n");
        }
    }

    check_red_properties(node->left);
    check_red_properties(node->right);
}


void check_rbtree_properties(struct rbtree *root) {
    if (root == NULL) return;

    // 1. Корень всегда черный
    if (root->color != BLACK) {
        printf("Ошибка: корень не черный.\n");
    }

    // 2. Проверка на два красных узла подряд
    check_red_properties(root);

    // 3. Проверка черной высоты
    int black_height = check_black_height(root);
    if (black_height == -1) {
        printf("Ошибка: разная черная высота в дереве.\n");
    } else {
        printf("Черная высота дерева: %d\n", black_height);
    }
}




int main() {
    struct rbtree *root = NULL;

    // Добавление узлов
    root = rbtree_add(root, 14, "thirty");
    root = rbtree_add(root, 11, "thirty");
    root = rbtree_add(root, 15, "thirty");
    root = rbtree_add(root, 2, "thirty");
    root = rbtree_add(root, 1, "thirty");
    root = rbtree_add(root, 7, "thirty");
    root = rbtree_add(root, 5, "thirty");
    root = rbtree_add(root, 8, "five");

    
   // check_rbtree_properties(root);
    rbtree_print_dfs(root, 0);

   
    root = rbtree_delete(root, 8);

    
    puts("Дерево после удаления элемента:");

    //check_rbtree_properties(root);
    rbtree_print_dfs(root, 0);

    return 0;
}
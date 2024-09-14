#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

 struct rbtree {
    int key;
    char *value;
    Color color;
    struct rbtree *left;
    struct rbtree *right;
    struct rbtree *parent;
}
//struct rbtree *satinelnode=NULL;


struct rbtree* createNode(int key, char *value) {
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
    node ->parent = parent;


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

int main() {
    struct rbtree *root = NULL;

    root = rbtree_add(root, 10, "aaab");
    root = rbtree_add(root, 20, "bbbd");
    root = rbtree_add(root, 30, "fffd");
    root = rbtree_add(root, 15, "hhhs");
    root = rbtree_add(root, 5, "gggd");

    rbtree_print_dfs(root, 0);

    return 0;
}
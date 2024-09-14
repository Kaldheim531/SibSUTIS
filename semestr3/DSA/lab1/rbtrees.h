#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct rbtree {
    int key;
    char *value;
    Color color;
    struct rbtree *left;
    struct rbtree *right;
    struct rbtree *parent;
} rbtree;

struct rbtree *rbtree_add(struct rbtree *root, int key,char *value);
struct rbtree *rbtree_lookup(struct rbtree *root,int key);
struct rbtree *rbtree_delete(struct rbtree *root,int key);
struct rbtree *rbtree_min(struct rbtree *root);
struct rbtree *rbtree_max(struct rbtree *root);
void rbtree_free(struct rbtree *root);
void rbtree_print_dfs(struct rbtree *root, int level);


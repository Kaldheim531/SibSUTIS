#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>


typedef enum { RED, BLACK } Color;

 struct rbtree {
    int key;
    char *value;
    Color color;
    struct rbtree *left;
    struct rbtree *right;
    struct rbtree *parent;
};

struct rbtree *rbtree_add(struct rbtree *root, int key,char *value);
struct rbtree *rbtree_lookup(struct rbtree *root,int key);
struct rbtree *rbtree_delete(struct rbtree *root,int key);
struct rbtree *rbtree_min(struct rbtree *root);
struct rbtree *rbtree_max(struct rbtree *root);
void rbtree_free(struct rbtree *root);
void rbtree_print_dfs(struct rbtree *root, int level);

struct rbtree* CreateNode(int key, char *value);
void leftRotate(struct rbtree **root, struct rbtree *x);
void rightRotate(struct rbtree **root, struct rbtree *x);
void RBTree_Add_Fixup(struct rbtree **root, struct rbtree *z);
void rbtree_delete_fixup(struct rbtree **root, struct rbtree *x);
void rbtree_transplant(struct rbtree **root, struct rbtree *u, struct rbtree *v);

double wtime();
int getrand(int min, int max);
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>
#include <stdint.h>
#define ALPHABET_SIZE 26

struct bstree { //Узел
    char *key;
    int value;
    struct bstree *left;
    struct bstree *right;
};


struct bstree *bstree_create(char* key, int value);
void bstree_add(struct bstree *tree, char *key, int value);
struct bstree *bstree_lookup(struct bstree *tree, char *key);
struct bstree *bstree_delete(struct bstree *tree, struct bstree *current, struct bstree *parent);
void REPLACE_NODE(struct bstree *parent, struct bstree *current, struct bstree *child);
struct bstree *delete(struct bstree *tree, char* key);
struct bstree *bstree_min(struct bstree *tree);
struct bstree *bstree_max(struct bstree *tree);
struct bstree *successor(struct bstree *tree, char* key);
struct bstree *predecessor(struct bstree *tree, char* key);
double wtime();
int getrand(int min, int max);
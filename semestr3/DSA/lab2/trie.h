#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>


struct trie {
    char *value;
    char ch;
    struct trie *sibling; /* Sibling node */
    struct trie *child; /* First child node */
};


struct trie *trie_create();
struct trie *trie_insert(struct trie *root, char *key, char *value);
char * trie_lookup(struct trie *root, char *key) ;
struct trie *trie_delete_dfs(struct trie *root, struct trie *parent, char *key, int *found);
struct trie *trie_delete(struct trie *root, char *key);
void trie_print(struct trie *root, int level);

double wtime();
int getrand(int min, int max);
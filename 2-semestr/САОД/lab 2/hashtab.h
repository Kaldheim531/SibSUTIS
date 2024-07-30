
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>
#include <stdint.h>

struct listnode{

    char *key;
    int value;
    struct listnode *next;
};
struct listnode *Create_Node_ta(int value);

unsigned int KRHash(char *key);
unsigned int FNVHash (char *buf);


void hashtab_init(struct listnode **hashtab);
void hashtab_add(struct listnode **hashtab, char *key, int value);
struct listnode *hashtab_lookup(struct listnode **hashtab, char *key);
void hashtab_delete(struct listnode **hashtab, char *key);
void hashtab_add_FNV(struct listnode **hashtab, char *key, int value, int *collisions);
struct listnode *hashtab_lookup_FNV(struct listnode **hashtab, char *key);

void hashtab_add_KP(struct listnode **hashtab, char *key, int value, int *collisions);
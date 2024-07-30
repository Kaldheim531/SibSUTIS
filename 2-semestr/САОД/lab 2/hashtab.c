#include "hashtab.h"
#define HASH_SIZE 200003

const unsigned FNV_32_PRIME = 0x01000193;

unsigned int FNVHash(char *buf) {
    unsigned int hval = 0x811c9dc5;
    const unsigned int modulus = 200000; // Максимальное значение для диапазона от 0 до 199999

    while (*buf) {
        hval ^= (unsigned int)*buf++;
        hval *= 0x01000193;
        hval %= modulus; // Применяем модуль для ограничения значения хэша
    }

    return hval;
}

unsigned int KRHash(char *key) // хеш-функция KRHASH
{
    unsigned int h = 0, hash_mul = 31;
    while (*key)
        h = h * hash_mul + (unsigned int)*key++;
    return h % HASH_SIZE;
}




struct listnode *Create_Node_ta(int value) {
    struct listnode* node = (struct listnode*)malloc(sizeof(struct listnode));
    node->value = value;
    node->next = NULL;
    return node;
}

// Инициализация хеш таблицы
void hashtab_init(struct listnode **hashtab)
{ // зануляет все элементы хеш таблицы, необходимо перед началом работы с ней
    for (int i = 0; i < HASH_SIZE; i++)
    {
        hashtab[i] = NULL;
    }
}

// Добавление элементов
void hashtab_add(struct listnode **hashtab, char *key, int value) {
    unsigned int hash = KRHash(key);
    
    
    struct listnode *node;
    node = malloc(sizeof(*node));
    if (node != NULL) {
        node->key = key;
        node->value = value;
        node->next = hashtab[hash];
        hashtab[hash] = node;
    }
    
}


void hashtab_add_KP(struct listnode **hashtab, char *key, int value, int *collisions) {

    
    unsigned int hash = KRHash(key);

    if (hashtab[hash] != NULL) { // в заданном поле уже есть элемент
        (*collisions)++;  // Если есть, увеличиваем счетчик коллизий
    }

    struct listnode *node;
    node = malloc(sizeof(*node));
    if (node != NULL) {
        node->key = key;
        node->value = value;
        node->next = hashtab[hash];
        hashtab[hash] = node;
    }
}

void hashtab_add_FNV(struct listnode **hashtab, char *key, int value, int *collisions)
{
    unsigned int  hash = FNVHash(key);

    if (hashtab[hash] != NULL) {
        (*collisions)++;
    }

    struct listnode *node;
    node = malloc(sizeof(*node));
    if (node != NULL) {
        node->key = key;
        node->value = value;
        node->next = hashtab[hash];
        hashtab[hash] = node;
    }
}

// Поиск элемента
struct listnode *hashtab_lookup(struct listnode **hashtab, char *key) {
    struct listnode *node;

    int index = KRHash(key);
    for (node = hashtab[index]; node != NULL; node = node->next) {
        if (0 == strcmp(node->key, key))
        return node;
    }
    return NULL;
}


// Поиск элемента
struct listnode *hashtab_lookup_FNV(struct listnode **hashtab, char *key) {
    struct listnode *node;

    int index = FNVHash(key);
    for (node = hashtab[index]; node != NULL; node = node->next) {
    if (0 == strcmp(node->key, key))
    return node;
    }
    return NULL;
}






// Удаление элемента
void hashtab_delete(struct listnode **hashtab, char *key)
{
    struct listnode *node, *prev = NULL;
    int index = KRHash(key);
    for (node = hashtab[index]; node != NULL; node = node->next) {
        if (0 == strcmp(node->key, key)) {
            if (prev == NULL)
                hashtab[index] = node->next;
            else
                prev->next = node->next;
            free(node);
            return;
        }
        prev = node;
    }
}



#include"trie.h"

// Создание нового узла Trie
struct trie *trie_create() 
{
    struct trie *node;

    if ((node = malloc(sizeof(*node))) == NULL)
        return NULL;
    node->ch = '\0';
    node->value = NULL;
    node->sibling = NULL;
    node->child = NULL;

    return node;
}

// Вставка ключа и значения в Trie
struct trie *trie_insert(struct trie *root, char *key, char *value) 
{
    struct trie *node, *parent, *list;

    parent = NULL;
    list = root;
    for (; *key != '\0'; key++) {
        // Lookup sibling node
        for (node = list; node != NULL; node = node->sibling) {
            if (node->ch == *key)
                break;
        }
        if (node == NULL) {                 // Node not found. Add new node
            node = trie_create();
            node->ch = *key;
            node->sibling = list;
            if (parent != NULL)
                parent->child = node;
            else
                root = node;
            list = NULL;
        } else {                // Node found. Move to next level
            list = node->child;
        }
        parent = node;
    }
    // Update value in leaf
    if (node->value != NULL)
        free(node->value);
    node->value = strdup(value);
    return root;
}

// Поиск значения по ключу в Trie
char* trie_lookup(struct trie *root, char *key) 
{
    struct trie *node, *list;

    for (list = root; *key != '\0'; key++) {
        for (node = list; node != NULL; node = node->sibling) {
            if (node->ch == *key)
                break;
        }
        if (node != NULL)
            list = node->child;
        else
            return NULL;
    }
    if (node != NULL && node->value != NULL) {
        return node->value; // Node must be a leaf
    }
    return NULL;
}

// Удаление ключа из Trie
struct trie *trie_delete(struct trie *root, char *key)
{
    int found;

    return trie_delete_dfs(root, NULL, key, &found);
}

// Рекурсивное удаление ключа из Trie
struct trie *trie_delete_dfs(struct trie *root, struct trie *parent, char *key, int *found)
{
    struct trie *node, *prev = NULL;

    *found = (*key == '\0' && root == NULL) ? 1 : 0;
    if (root == NULL || *key == '\0')
        return root;
    
    for (node = root; node != NULL; node = node->sibling) {
        if (node->ch == *key)
            break;
        prev = node;
    }
    if (node == NULL)
        return root;
    trie_delete_dfs(node->child, node, key + 1, found);
    if (*found > 0 && node->child == NULL) {
        // Delete node
        if (prev != NULL)
            prev->sibling = node->sibling;
        else {
            if (parent != NULL)
                parent->child = node->sibling;
            else
                root = node->sibling;
        }
        free(node->value);
        free(node);
    }
    return root;
}

void trie_print(struct trie *root, int level) {
    if (root == NULL)
        return;

    // Выводим текущий узел
    for (int i = 0; i < level; i++) {
        printf("  "); // Отступ для визуализации уровня вложенности
    }
    printf("(%c)", root->ch);
    if (root->value != NULL) {
        printf(" -> %s", root->value);
    }
    printf("\n");

    // Рекурсивно выводим детей
    if (root->child != NULL) {
        trie_print(root->child, level + 1);
    }

    // Рекурсивно выводим сиблингов
    if (root->sibling != NULL) {
        trie_print(root->sibling, level);
    }
}



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
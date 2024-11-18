#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Определение цвета узла
typedef enum { RED, BLACK } Color;

// Определение структуры узла дерева
typedef struct Node {
    int key;
    int val;
    Color color;
    struct Node *left, *right;
} Node;

// Прототипы функций
Node* createNode(int key, int val);
bool isRed(Node* node);
Node* rotateLeft(Node* h);
Node* rotateRight(Node* h);
void flipColors(Node* h);
Node* min(Node* node);
Node* deleteMin(Node* h);
Node* moveRedLeft(Node* h);
Node* moveRedRight(Node* h);
Node* balance(Node* h);
Node* delete(Node* h, int key);
void printTree(Node* root, int level);
Node* insert(Node* h, int key, int val);
Node* search(Node* root, int key);
int black_height(Node* root);
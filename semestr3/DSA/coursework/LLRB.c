#include "LLRB.h"

// Создание нового узла
Node* createNode(int key, int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->val = val;
    node->color = RED; // Новые узлы всегда красные
    node->left = node->right = NULL;
    return node;
}

// Проверка, является ли узел красным
bool isRed(Node* node) {
    return node != NULL && node->color == RED;
}

// Левый поворот
Node* rotateLeft(Node* h) {
    Node* x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

// Правый поворот
Node* rotateRight(Node* h) {
    Node* x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

// Смена цветов
void flipColors(Node* h) {
    h->color = RED;
    h->left->color = BLACK;
    h->right->color = BLACK;
}

// Нахождение минимального узла в поддереве
Node* min(Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

// Удаление минимального узла
Node* deleteMin(Node* h) {
    if (h->left == NULL)
        return NULL;

    if (!isRed(h->left) && !isRed(h->left->left))
        h = moveRedLeft(h);

    h->left = deleteMin(h->left);
    return balance(h);
}

// Перемещение красного узла влево
Node* moveRedLeft(Node* h) {
    flipColors(h);
    if (isRed(h->right->left)) {
        h->right = rotateRight(h->right);
        h = rotateLeft(h);
        flipColors(h);
    }
    return h;
}

// Перемещение красного узла вправо
Node* moveRedRight(Node* h) {
    flipColors(h);
    if (isRed(h->left->left)) {
        h = rotateRight(h);
        flipColors(h);
    }
    return h;
}

// Восстановление инвариантов красно-черного дерева
Node* balance(Node* h) {
    if (isRed(h->right) && !isRed(h->left))    h = rotateLeft(h);  // Принудительное вращение влево
    if (isRed(h->left) && isRed(h->left->left)) h = rotateRight(h); // Балансировка узла с 4-я потомками
    if (isRed(h->left) && isRed(h->right))     flipColors(h); // Расщепление узла с 4-я потомками
    return h;
}

// Удаление узла с заданным ключом
Node* delete(Node* h, int key) {
    if (key < h->key) {
        if (!isRed(h->left) && !isRed(h->left->left)) 
            h = moveRedLeft(h);
        h->left = delete(h->left, key);
    } else {
        if (isRed(h->left))
            h = rotateRight(h);
        if (key == h->key && (h->right == NULL)) {
            free(h);
            return NULL; // Случай 1 и Случай 2
        }
        if (!isRed(h->right) && !isRed(h->right->left))
            h = moveRedRight(h);
        if (key == h->key) { //Случай 3: Узел имеет 2 наследников
            Node* x = min(h->right);
            h->key = x->key;
            h->val = x->val;
            h->right = deleteMin(h->right);
        } else {
            h->right = delete(h->right, key);
        }
    }
    return balance(h);
}

Node* insert(Node* h, int key, int val) {
    if (h == NULL)
        return createNode(key, val);

    if (key < h->key)
        h->left = insert(h->left, key, val);
    else if (key > h->key)
        h->right = insert(h->right, key, val);
    else
        h->val = val; // Обновляем значение, если ключ уже существует

    // Принудительное вращение влево
    if (isRed(h->right) && !isRed(h->left))
        h = rotateLeft(h);

    // Балансировка узла с 4-я потомками
    if (isRed(h->left) && isRed(h->left->left))
        h = rotateRight(h);

    // Расщепление узла с 4-я потомками
    if (isRed(h->left) && isRed(h->right))
        flipColors(h);

    return h;
}

// Вспомогательная функция для печати дерева (для отладки)
void printTree(Node* root, int level) {
    if (root == NULL)
        return;
    printTree(root->right, level + 1);
    for (int i = 0; i < level; i++)
        printf("    ");
    printf("%d (%s)\n", root->key, root->color == RED ? "RED" : "BLACK");
    printTree(root->left, level + 1);
}
// Функция поиска узла по ключу
Node* search(Node* root, int key) {
    Node* current = root;
    while (current != NULL) {
        if (key == current->key) {
            return current; // Узел найден
        } else if (key < current->key) {
            current = current->left; // Идем влево
        } else {
            current = current->right; // Идем вправо
        }
    }
    return NULL; // Узел не найден
}
// Функция для вычисления черной высоты дерева
int black_height(Node* root) {
    if (root == NULL)
        return 0; // Пустое дерево имеет черную высоту 0

    int left_black_height = black_height(root->left);
    int right_black_height = black_height(root->right);

    // Если текущий узел черный, увеличиваем черную высоту на 1
    if (root->color == BLACK)
        return 1 + left_black_height;
    else
        return left_black_height;
}
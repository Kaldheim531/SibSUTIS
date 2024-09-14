rbtree *rotate_left(rbtree *root, rbtree *x) {
    rbtree *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    return root;
}

rbtree *rotate_right(rbtree *root, rbtree *y) {
    rbtree *x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
        root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
    return root;
}

void RBTree_Add_Fixup(rbtree **root, rbtree *node) {
    while (node != *root && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            rbtree *uncle = node->parent->parent->right;
            if (uncle != NULL && uncle->color == RED) {
                // Случай 1: дядя красный
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    // Случай 2: дядя черный, узел - правый потомок
                    node = node->parent;
                    *root = rotate_left(*root, node);
                }
                // Случай 3: дядя черный, узел - левый потомок
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                *root = rotate_right(*root, node->parent->parent);
            }
        } else {
            rbtree *uncle = node->parent->parent->left;
            if (uncle != NULL && uncle->color == RED) {
                // Случай 1: дядя красный
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    // Случай 2: дядя черный, узел - левый потомок
                    node = node->parent;
                    *root = rotate_right(*root, node);
                }
                // Случай 3: дядя черный, узел - правый потомок
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                *root = rotate_left(*root, node->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}
#include "bstree.h"


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
struct bstree *bstree_create(char* key, int value)
{
    struct bstree *new_node = (struct bstree*)malloc(sizeof(struct bstree));

    if (new_node != NULL)
    {
        new_node->key = strdup(key);
        if (new_node->key == NULL) {
            free(new_node);
            return NULL;
        }
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}
void bstree_add(struct bstree *tree, char* key, int value)
{

    struct bstree *parent = NULL;
    while(tree != NULL)
    {
        parent = tree;

        int cmp = strcmp(key, tree->key);
        if(cmp < 0)
            tree = tree->left;
        else if(cmp > 0)
            tree = tree->right;
        else
        {
            return;
        }
    }


    struct bstree *new_node = bstree_create(key, value);

    if (new_node == NULL)
        return;

    int cmp = strcmp(key, parent->key);
    if(cmp > 0)
        parent->right = new_node;
    else
        parent->left = new_node;
}


struct bstree *bstree_lookup(struct bstree *tree, char* key)
{
    while(tree != NULL)
    {
        int cmp = strcmp(key, tree->key);
        if(cmp > 0)
            tree = tree->right;
        else if(cmp < 0)
            tree = tree->left;
        else
            return tree;
    }

    return NULL;
}


struct bstree *bstree_min(struct bstree *tree)
{
    while(tree->left != NULL)
    {
        tree = tree->left;
    }

    return tree;
}

struct bstree *bstree_max(struct bstree *tree)
{
    while(tree->right != NULL)
    {
        tree = tree->right;
    }

    return tree;
}

struct bstree *successor(struct bstree *tree, char* key)
{
    struct bstree *successor = NULL;

    while(tree != NULL)
    {

        if(strcmp(key, tree->key) > 0)
        {
            tree = tree->right;
        }

        else if(strcmp(key, tree->key) < 0)
        {
            successor = tree;
            tree = tree->left;
        }

        else
        {
            if(tree->right != NULL)
                return bstree_min(tree->right);
            return successor;
        }

    }

    return NULL;


}

struct bstree *predecessor(struct bstree *tree, char* key)
{
    struct bstree *predecessor = NULL;

    while(tree != NULL)
    {

        if(strcmp(key, tree->key) > 0)
        {
            predecessor = tree;
            tree = tree->right;
        }

        else if(strcmp(key, tree->key) < 0)
        {
            tree = tree->left;
        }

        else
        {
            if(tree->left != NULL)
                return bstree_max(tree->left);
            return predecessor;
        }
    }

    return NULL;
}

void REPLACE_NODE(struct bstree *parent, struct bstree *current, struct bstree *child)
{
    if(parent != NULL)
    {
        if(strcmp(current->key, parent->key) < 0)
        {
            parent->left = child;
        }

        else
        {
            parent->right = child;
        }
    }
}



struct bstree *delete(struct bstree *tree, char* key)
{
    struct bstree *parent = NULL;
    struct bstree *current = tree;
    while(current != NULL && strcmp(key, current->key) != 0)
    {
        parent = current;

        if(strcmp(key, current->key) < 0)
        {

            current = current->left;
        }

        else
        {
            current = current->right;
        }
    }

    if(current == NULL)
    {
        return tree;
    }

    return bstree_delete(tree, current, parent);
}

struct bstree *bstree_delete(struct bstree *tree, struct bstree *current, struct bstree *parent)
{
    if(current->left != NULL)
    {
        REPLACE_NODE(parent, current, current->right);
        if(parent == NULL)
        {
            tree = current->right;
        }
    }

    else if(current->right != NULL)
    {
        REPLACE_NODE(parent, current, current->left);
        if(parent == NULL)
        {
            tree = current->left;
        }
    }

    else
    {
        struct bstree *min = current->right;
        struct bstree *minparent = min;

        while(min->left != NULL)
        {
            minparent = min;
            min = min->left;
        }

        REPLACE_NODE(parent, current, min);
        if(parent == NULL)
            tree = min;
        if(current->right != min)
        {
            minparent->left = min->right;
            min->left = current->left;
            min->right = current->right;
        }

        else
        {
            min->left = current->left;
        }

        free(current->key);
        free(current);
    }

    return tree;

}
#include "bstree.h"
#include <stdlib.h>
#include <string.h>

unsigned int hash(char *key)
{
    unsigned int h = 0, hash_mul = 31;
    while (*key)
        h = h * hash_mul + (unsigned int)*key++;
    return h % 200000;
}

bstree *bstree_create(char *key, int value)
{
    bstree *node;
    node = malloc(sizeof(*node));
    if (node)
    {
        node->key = key;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void bstree_add(bstree *tree, char *key, int value)
{
    if (!tree)
        return;
    bstree *parent, *node;
    while (tree)
    {
        parent = tree;
        if (hash(key) < hash(tree->key))
            tree = tree->left;
        else if (hash(key) > hash(tree->key))
            tree = tree->right;
        else
            return;
    }
    node = bstree_create(key, value);
    if (hash(key) < hash(parent->key))
        parent->left = node;
    else
        parent->right = node;
}

bstree *bstree_lookup(bstree *tree, char *key)
{
    while (tree)
    {
        if (hash(key) == hash(tree->key))
            return tree;
        else if (hash(key) < hash(tree->key))
            tree = tree->left;
        else
            tree = tree->right;
    }
    return tree;
}

bstree *bstree_min(bstree *tree)
{
    if (!tree)
        return NULL;
    while (tree->left)
        tree = tree->left;
    return tree;
}

bstree *bstree_max(bstree *tree)
{
    if (!tree)
        return NULL;
    while (tree->right)
        tree = tree->right;
    return tree;
}

bstree *bstree_parent(bstree *tree, char *key)
{
    if (!tree)
        return NULL;
    bstree *parent;
    while (tree)
    {
        parent = tree;
        if (hash(key) < hash(tree->key))
            tree = tree->left;
        else if (hash(key) > hash(tree->key))
            tree = tree->right;
        else
            return NULL;
    }
    return parent;
}

struct bstree *bstree_delete(struct bstree *tree, char *key)
{
    struct bstree *parent = NULL;
    struct bstree *node = tree;

    if (!node)
    {
        return tree;
    }

    while (node)
    {
        parent = tree;
        if (hash(key) < hash(tree->key))
            tree = tree->left;
        else if (hash(key) > hash(tree->key))
            tree = tree->right;
        else
            return;
    }

    if (!node->left && !node->right)
    {
        if (!parent)
        {
            free(node);
            return NULL;
        }
        else if (parent->left == node)
        {
            parent->left = NULL;
        }
        else
        {
            parent->right = NULL;
        }
        free(node);
    }
    else if (!node->left || !node->right)
    {
        struct bstree *child = node->left ? node->left : node->right;
        if (!parent)
        {
            free(node);
            return child;
        }
        else if (parent->left == node)
        {
            parent->left = child;
        }
        else
        {
            parent->right = child;
        }
        free(node);
    }

    else
    {
        struct bstree *min = bstree_min(node->right);
        node->key = min->key;
        node->value = min->value;
        tree->right = bstree_delete(tree->right, min->key);
    }

    return tree;
}
#include "bstree.h"
#include <stdlib.h>
#include <string.h>

unsigned int hash(char *s)
{
    unsigned int h = 0;
    while (*s)
        h += (unsigned int)*s++;
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

// bstree *bstree_delete(bstree *tree, char *key)
// {
//     bstree *node = bstree_lookup(tree, key);
//     bstree *parent = bstree_parent(tree, key);
//     if (node->left == NULL && node->right == NULL)
//     {
//         if (parent->left == node)
//         {
//             free(node);
//             parent->left = NULL;
//         }
//         else
//         {
//             free(node);
//             parent->right = NULL;
//         }
//         printf("1\n");
//     }
//     else if ((node->left == NULL && node->right != NULL) || (node->right == NULL || node->left != NULL))
//     {
//         bstree *tmp = NULL;
//         if (node->left == NULL)
//             tmp = node->right;
//         else
//             tmp = node->left;
//         if (parent->left == node)
//             parent->left = tmp;
//         else
//             parent->right = tmp;
//         free(node);
//         printf("2\n");
//     }
//     else if (node->right != NULL && node->left != NULL)
//     {
//         bstree *tmp = bstree_min(node->right);
//         printf("%d\n", tmp->key);
//         if (parent->left == node)
//         {
//             parent->left->key = tmp->key;
//             parent->left->value = strdup(tmp->value);
//         }
//         else
//         {
//             parent->right->key = tmp->key;
//             parent->right->value = strdup(tmp->value);
//         }
//         printf("3\n");
//     }
//     return tree;
// }
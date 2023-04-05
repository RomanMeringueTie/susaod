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

// struct node *deleteNode(struct node *root, int key)
// {
//     // base case
//     if (root == NULL)
//         return root;

//     // If the key to be deleted is smaller than the
//     // root's key, then it lies in left subtree
//     if (key < root->key)
//         root->left = deleteNode(root->left, key);

//     // If the key to be deleted is greater than the root's key,
//     // then it lies in right subtree
//     else if (key > root->key)
//         root->right = deleteNode(root->right, key);

//     // if key is same as root's key
//     else
//     {
//         // If key is present more than once, simply decrement
//         // count and return
//         if (root->count > 1)
//         {
//             (root->count)--;
//             return root;
//         }

//         // ElSE, delete the node

//         // node with only one child or no child
//         if (root->left == NULL)
//         {
//             struct node *temp = root->right;
//             free(root);
//             return temp;
//         }
//         else if (root->right == NULL)
//         {
//             struct node *temp = root->left;
//             free(root);
//             return temp;
//         }

//         // node with two children: Get the inorder successor (smallest
//         // in the right subtree)
//         struct node *temp = minValueNode(root->right);

//         // Copy the inorder successor's content to this node
//         root->key = temp->key;
//         root->count = temp->count;

//         // Delete the inorder successor
//         root->right = deleteNode(root->right, temp->key);
//     }
//     return root;
// }

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
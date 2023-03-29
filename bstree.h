#include <stdio.h>
#pragma once
struct bstree
{
    char *key;
    int value;
    struct bstree *left;
    struct bstree *right;
};
typedef struct bstree bstree;

bstree *bstree_create(char *key, int value);

void bstree_add(struct bstree *tree, char *key, int value);

bstree *bstree_lookup(struct bstree *tree, char *key);

bstree *bstree_delete(struct bstree *tree, char *key);

bstree *bstree_min(struct bstree *tree);

bstree *bstree_max(struct bstree *tree);

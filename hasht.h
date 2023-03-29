#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma once
#define HASHTAB_SIZE 200000

struct listnode
{
    char *key;
    int value;

    struct listnode *next;
};
typedef struct listnode listnode;

unsigned int hashtab_hash(char *key);

void hashtab_init(struct listnode **hashtab);

void hashtab_add(struct listnode **hashtab, char *key, int value);

struct listnode *hashtab_lookup(struct listnode **hashtab, char *key);

void hashtab_delete(struct listnode **hashtab, char *key);

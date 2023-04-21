#include "hasht.h"
#define HASHTAB_SIZE 200000

unsigned int ADDHash(char *s)
{
    unsigned int h = 0;
    while (*s)
        h += (unsigned int)*s++;
    return h % HASHTAB_SIZE;
}

unsigned int KRHash(char *key)
{
    unsigned int h = 0, hash_mul = 13131;
    while (*key)
        h = h * hash_mul + (unsigned int)*key++;
    return h % HASHTAB_SIZE;
}

unsigned int XORHash(char *key)
{
    unsigned int h = 0;
    while (*key)
    {
        h = ((h << 5) + h) ^ (unsigned int)*key;
        key++;
    }
    return h % HASHTAB_SIZE;
}

void hashtab_init(struct listnode **hashtab)
{
    int i;

    for (i = 0; i < HASHTAB_SIZE; i++)
        hashtab[i] = NULL;
}

void hashtab_add(struct listnode **hashtab, char *key, int value, int hf)
{
    listnode *node;
    int index = 0;
    if (hf == 1)
        index = KRHash(key);
    else
        index = XORHash(key);
    node = malloc(sizeof(*node));
    if (node != NULL)
    {
        node->key = key;
        node->value = value;
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}

struct listnode *hashtab_lookup(struct listnode **hashtab, char *key, int hf)
{
    listnode *node;
    int index = 0;
    if (hf == 1)
        index = KRHash(key);
    else
        index = XORHash(key);
    for (node = hashtab[index]; node != NULL; node = node->next)
    {
        if (0 == strcmp(node->key, key))
            return node;
    }
    return NULL;
}

void hashtab_delete(struct listnode **hashtab, char *key)
{
    listnode *node, *prev = NULL;
    int index = KRHash(key);
    for (node = hashtab[index]; node != NULL; node = node->next)
    {
        if (0 == strcmp(node->key, key))
        {
            if (prev == NULL)
                hashtab[index] = node->next;
            else
                prev->next = node->next;
            free(node);
            return;
        }
        prev = node;
    }
}
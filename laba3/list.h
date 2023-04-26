#pragma once

struct listnode
{
    char *key;             /* Ключ */
    int value;             /* Значение */
    struct listnode *next; /* Указатель на следующий элемент */
};

struct listnode *list_createnode(char *key, int value);

struct listnode *list_addfront(struct listnode *list, char *key, int value);

struct listnode *list_lookup(struct listnode *list, char *key);

struct listnode *list_delete(struct listnode *list, char *key);

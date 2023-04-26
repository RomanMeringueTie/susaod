#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct listnode *list_createnode(char *key, int value)
{
    struct listnode *p;

    p = malloc(sizeof(*p));
    if (p != NULL)
    {
        p->key = key;
        p->value = value;
        p->next = NULL;
    }
    return p;
}

struct listnode *list_addfront(struct listnode *list, char *key, int value)
{
    struct listnode *newnode;
    newnode = list_createnode(key, value);

    if (newnode != NULL)
    {
        newnode->next = list;
        return newnode;
    }
    return list;
}

struct listnode *list_lookup(struct listnode *list, char *key)
{
    for (; list != NULL; list = list->next)
    {
        if (strcmp(list->key, key) == 0)
        {
            return list;
        }
    }
    return NULL; /* Не нашли */
}

struct listnode *list_delete(struct listnode *list, char *key)
{
    struct listnode *p, *prev = NULL;
    for (p = list; p != NULL; p = p->next)
    {
        if (strcmp(p->key, key) == 0)
        {
            if (prev == NULL)
                list = p->next; /* Удаляем голову */
            else
                prev->next = p->next; /* Есть элемент слева */
            free(p);                  /* Освобождаем память */
            return list;              /* Указатель на новую голову */
        }
        prev = p; /* Запоминаем предыдущий элемент */
    }
    return NULL; /* Не нашли */
}
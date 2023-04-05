#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"
#include <sys/time.h>
#include <time.h>

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int main()
{
    FILE *file;
    file = fopen("words.txt", "r+");
    int n = 200001;
    char string[n][20];
    for (int i = 0; i < n; i++)
        fgets(string[i], n - 1, file);
    fclose(file);
    bstree *tree = bstree_create(string[0], 0);
    int count = 0;
    for (int i = 1; i < n; i++)
    {
        bstree_add(tree, string[i - 1], i - 1);
        if (i % 10000 == 0)
        {
            char *w = string[getrand(0, i)];
            clock_t t;
            t = clock();
            bstree *node1 = bstree_lookup(tree, w);
            t = clock() - t;
            double time_taken = ((double)t) / CLOCKS_PER_SEC;
            printf("%d: n = %d, time = %lf.10\n", ++count, i, time_taken);
        }
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"
#include <sys/time.h>

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

int main(int argc, char **argv)
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
        bstree_add(tree, string[i], i);
        if (i % 10000 == 0)
        {
            char *w = string[getrand(0, i)];
            double t = wtime();
            bstree *node1 = bstree_lookup(tree, w);
            t = wtime() - t;
            printf("%d: n = %d, time = %.10lf\n", ++count, i, t);
        }
    }
    return 0;
}
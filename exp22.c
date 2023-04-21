#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"
#include <sys/time.h>
#include <time.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int main()
{
    FILE *file;
    file = fopen("wordsaverage.txt", "r+");
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
            clock_t t;
            t = clock();
            bstree *node1 = bstree_max(tree);
            t = clock() - t;
            double time_taken = ((double)t) / CLOCKS_PER_SEC;
            printf("%d: n = %d, time = %lf\n", ++count, i, time_taken);
        }
    }
    return 0;
}
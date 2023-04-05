#include <stdio.h>
#include <stdlib.h>
#include "hasht.h"
#include <sys/time.h>
#include <time.h>

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
    listnode *table[200000];
    hashtab_init(table);
    int count = 0;
    int collisions = 0;
    listnode *node = NULL;
    for (int i = 1; i < n; i++)
    {
        hashtab_add(table, string[i - 1], i - 1);
        if (i % 10000 == 0)
        {
            char *w = string[getrand(0, i - 1)];
            collisions = 0;
            clock_t t;
            t = clock();
            node = hashtab_lookup(table, w);
            t = clock() - t;
            double time_taken = ((double)t) / CLOCKS_PER_SEC;
            printf("%d: n = %d, time = %.6lf, ", ++count, i, time_taken);
            if (node == NULL)
                printf("!!!!!!!!!!!!!!!!!!!!!!!!!");
            for (int j = 0; j < i; j++)
            {
                if (table[j] != NULL)
                    collisions++;
            }
            printf("Number of collisions = %d\n", i - collisions);
        }
    }
    return 0;
}
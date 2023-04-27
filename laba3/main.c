#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "graph.h"
#include "graph.h"
#include "queue.h"
#include "dijkstra.h"

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

void print1d(int *arr, int len)
{
    for (int i = 1; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void print2d(int **arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}

int linked_graph()
{
    struct graph *linked = graph_create(20);
    for (int i = 0; i < linked->nvertices - 1; i++)
    {
        graph_set_edge(linked, i, i + 1, getrand(10, 30));
    }
    for (int j = 0; j < linked->nvertices; j++)
    {
        for (int i = 0; i < linked->nvertices - 1; i++)
        {
            int x = getrand(1, linked->nvertices - 1);
            int y = getrand(x + 1, linked->nvertices - 1);
            graph_set_edge(linked, x, y, getrand(10, 30));
        }
    }
    // printf("Матрица смежности:\n");
    // print2d(linked->m, linked->nvertices);
    struct heap *q = heap_create(linked->nvertices);
    double t = wtime();
    dijkstra(q, linked, 1);
    t = wtime() - t;
    printf("Время работы алгоритма Дейкстры: %.10lf\n", t);
    printf("Самые короткие пути из вершины 1:\n");
    print1d(linked->d, linked->nvertices + 1);
    printf("Кратчайший путь из вершины 1 в вершину 10:\n");
    shortest(q, linked, 1, 10);
    return 0;
}

int lattice_graph()
{
    struct graph *lattice = graph_create(100);
    for (int i = 0; i < lattice->nvertices - 2; i++)
    {
        if (i % 2 == 0)
        {
            graph_set_edge(lattice, i, i + 1, getrand(10, 30));
            graph_set_edge(lattice, i, i + 2, getrand(10, 30));
        }
        else
            graph_set_edge(lattice, i, i + 2, getrand(10, 30));
    }
    graph_set_edge(lattice, lattice->nvertices - 1, lattice->nvertices - 2, getrand(10, 30));
    // printf("Матрица смежности:\n");
    // print2d(lattice->m, lattice->nvertices);
    struct heap *q = heap_create(lattice->nvertices);
    double t = wtime();
    dijkstra(q, lattice, 1);
    t = wtime() - t;
    printf("Время работы алгоритма Дейкстры: %.10lf\n", t);
    printf("Самые короткие пути из вершины 1:\n");
    print1d(lattice->d, lattice->nvertices + 1);
    printf("Кратчайший путь из вершины 1 в вершину 50:\n");
    shortest(q, lattice, 1, 10);
    return 0;
}

int main()
{
    linked_graph();
    lattice_graph();
    return 0;
}

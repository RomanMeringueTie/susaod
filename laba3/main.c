#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "graph.h"
#include "queue.h"
#include "dijkstra.h"

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int main()
{
    struct graph *linked = graph_create(20);
    for (int i = 0; i < linked->nvertices - 1; i++)
    {
        graph_set_edge(linked, i, i + 1, getrand(1, 10));
    }
    int src[20];
    int prev[21];
    struct heap *h = dijkstra(linked, 0, src, prev);
    return 0;
}
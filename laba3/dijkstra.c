#include <stdlib.h>
#include <stdio.h>

#include "dijkstra.h"
#include "graph.h"
#include "heap.h"

void dijkstra(struct heap *q, struct graph *graph, int src)
{
    graph->h[src] = src;
    graph->d[src] = 0;
    graph->prev[src] = -1;
    heap_insert(q, graph->d[src], src);
    for (int i = 1; i < graph->nvertices + 1; i++)
    {
        if (i != src)
        {
            graph->h[i] = 0;
            graph->d[i] = 99999999;
            graph->prev[i] = -1;
            heap_insert(q, graph->d[i], i);
        }
    }
    for (int i = 1; i < graph->nvertices + 1; i++)
    {
        struct heapnode node = heap_extract_min(q);
        int v = node.value;
        graph->h[v] = v;
        for (int j = 1; j < graph->nvertices + 1; j++)
        {
            if (graph->m[v - 1][j - 1] && !graph->h[j])
            {
                if (graph->d[v] + graph->m[v - 1][j - 1] < graph->d[j])
                {
                    graph->d[j] = graph->d[v] + graph->m[v - 1][j - 1];
                    heap_increase_key(q, j, graph->d[j]);
                    graph->prev[j] = v;
                }
            }
        }
    }
}

void shortest(struct heap *q, struct graph *graph, int src, int dst)
{
    int i = dst;
    int pathlen = 1;
    while (i != src)
    {
        pathlen++;
        i = graph->prev[i];
    }
    int j = 0;
    i = dst;
    int path[graph->nvertices];
    while (i != src)
    {
        path[pathlen - j] = i;
        i = graph->prev[i];
        j++;
    }
    for (int i = 2; i < pathlen + 1; i++)
    {
        printf("%d ", path[i]);
    }
    printf("\n");
}

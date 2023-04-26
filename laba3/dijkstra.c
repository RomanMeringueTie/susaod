#include <stdlib.h>
#include <stdio.h>

#include "dijkstra.h"
#include "graph.h"
#include "heap.h"

struct heap *dijkstra(struct graph *g, int src, int *d, int *prev)
{
    struct heap *q = heap_create(g->nvertices);
    for (int i = 0; i < g->nvertices; i++)
    {
        d[i] = 1000;
        prev[i] = -1;
        heap_insert(q, i, d[i]);
    }
    d[src] = 0;
    prev[src] = -1;
    heap_insert(q, src, d[src]);
    for (int i = 0; i < g->nvertices; i++)
    {
        heap_extract_min(q);
        *g->visited = i;
        g->visited++;
    }
    for (int i = 0; i < g->nvertices; i++)
    {
        int is_visited = 0;
        for (int *j = g->visited; g->visited != NULL; j++)
        {
            if (i == *j)
            {
                is_visited = 1;
                break;
            }
        }
        if (is_visited)
        {
            for (int j = 0; j < g->nvertices; j++)
            {
                if (d[i] + g->m[i][j] < d[j])
                {
                    d[j] = d[i] + g->m[i][j];
                    heap_increase_key(q, j, d[j]);
                    prev[j] = i;
                }
            }
        }
    }
    return q;
}
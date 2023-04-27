#include <stdlib.h>
#include <stdio.h>

#include "graph.h"

struct graph *graph_create(int nvertices)
{
    struct graph *graph = malloc(sizeof(*graph));
    graph->nvertices = nvertices;
    graph->m = (int **)malloc(nvertices * sizeof(int *));
    for (int i = 0; i < nvertices; i++)
    {
        graph->m[i] = (int *)calloc(nvertices, sizeof(int));
    }
    graph->d = (int *)calloc(nvertices + 1, sizeof(int));
    graph->h = (int *)calloc(nvertices + 1, sizeof(int));
    graph->prev = (int *)calloc(nvertices + 1, sizeof(int));
    return graph;
}

void graph_free(struct graph *g)
{
    free(g->m);
    free(g->h);
    free(g->d);
    free(g->prev);
    free(g);
}

void graph_set_edge(struct graph *g, int i, int j, int w)
{
    g->m[i][j] = g->m[j][i] = w;
}

int graph_get_edge(struct graph *g, int i, int j)
{
    return g->m[i][j];
}

void graph_dfs(struct graph *g, int v)
{
    int i;
    g->h[v - 1] = 1;
    printf("Vertex % d\n", v);
    for (i = 0; i < g->nvertices; i++)
        if (g->m[(v - 1) * g->nvertices + i] > 0 && g->h[i] == 0)
            graph_dfs(g, i + 1);
}

void graph_bfs(struct graph *g, int v)
{
    int i, j;
    struct queue *q;
    for (i = 0; i < g->nvertices; i++)
        g->h[i] = 0;
    q = queue_create(g->nvertices); // Создаём очередь
    g->h[v - 1] = 1;                // Обрабатываем стартовую вершину
    printf("Vertex % d\n", v);
    queue_enqueue(q, v - 1);
    while (queue_size(q) > 0)
    {
        i = queue_dequeue(q);
        for (j = 0; j < g->nvertices; j++)
        {
            if (g->m[i * g->nvertices + j] > 0 && g->h[j] == 0)
            {
                queue_enqueue(q, j);
                g->h[j] = 1;
                printf("Vertex % d\n", j + 1);
            }
        }
    }
    queue_free(q);
}

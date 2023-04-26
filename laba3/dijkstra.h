#include "graph.h"
#include "heap.h"

struct heap *dijkstra(struct graph *g, int src, int *d, int *prev);
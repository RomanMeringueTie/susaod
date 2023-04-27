#pragma once

#include "graph.h"
#include "heap.h"

void dijkstra(struct heap *q, struct graph *graph, int src);

void shortest(struct heap *q, struct graph *graph, int src, int dst);
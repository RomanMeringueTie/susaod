all : app1

app1: graph.c heap.c queue.c main.c graph.c dijkstra.c
	gcc -Wall -g -O0 -o app1 heap.c queue.c main.c graph.c dijkstra.c

.PHONY: run

run: app1
	./app1
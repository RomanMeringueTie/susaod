all : app

app: graph.c heap.c queue.c main.c graph.c dijkstra.c
	gcc -Wall -g -O0 -o app heap.c queue.c main.c graph.c dijkstra.c

.PHONY: run

run: app
	./app
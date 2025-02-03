#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>

struct graph
{
    int nvertices; // Число вершин

    int *m; // Матрица n x n
    int *visited;
};

struct graph *graph_create(int nvertices);
void graph_set_edge(struct graph *g, int i, int j, int w);
int graph_get_edge(struct graph *g, int i, int j);
void graph_dfs(struct graph *g, int v);
void graph_bfs(struct graph *g, int v);
void graph_free(struct graph *g);
void graph_print(struct graph *g);

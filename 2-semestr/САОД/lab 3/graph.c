#include "graph.h"
#include "queue_array.h"

void graph_clear(struct graph *g) // устанавливая все посещенные вершины в непосещенное состояние (0) и все веса ребер в 0.
{
    int i, j;
    for (i = 0; i < g->nvertices; i++)
    {
        g->visited[i] = 0;
        for (j = 0; j < g->nvertices; j++)
        {
            g->m[i * g->nvertices + j] = 0;
        }
    }
}

struct graph *graph_create(int nvertices) /* Функция создает новый граф с заданным количеством вершин. Она выделяет память для матрицы смежности и массива посещенных вершин, а затем вызывает graph_clear для инициализации графа.*/
{
    struct graph *g;
    g = malloc(sizeof(*g));
    g->nvertices = nvertices;
    g->m = malloc(sizeof(int) * nvertices * nvertices);
    g->visited = malloc(sizeof(int) * nvertices);
    graph_clear(g); // Опционально, O(n^2)
    return g;
}

void graph_set_edge(struct graph *g, int i, int j, int w) /*Функция устанавливает вес ребра между двумя вершинами в графе. */
{
    g->m[(i - 1) * g->nvertices + j - 1] = w;
    g->m[(j - 1) * g->nvertices + i - 1] = w;
}

int graph_get_edge(struct graph *g, int i, int j)
{
    return g->m[(i - 1) * g->nvertices + j - 1];
}

void graph_dfs(struct graph *g, int v) // рекурсивный обход всех смежных вершин и помечаем посещенные вершины
{
    int i;
    g->visited[v - 1] = 1;
    printf("Vertex % d\n", v);

    for (i = 0; i < g->nvertices; i++)
        if (g->m[(v - 1) * g->nvertices + i] > 0 && g->visited[i] == 0)
            graph_dfs(g, i + 1);
}

void graph_bfs(struct graph *g, int v)
{
    int i, j;
    struct queue *q;
    for (i = 0; i < g->nvertices; i++)
        g->visited[i] = 0;
    q = queue_create(g->nvertices); // Создаём очередь
    g->visited[v - 1] = 1;          // Обрабатываем стартовую вершину
    printf("Vertex % d\n", v);
    queue_enqueue(q, v - 1);
    while (queue_size(q) > 0)
    {
        i = queue_dequeue(q);
        for (j = 0; j < g->nvertices; j++)
        {
            if (g->m[i * g->nvertices + j] > 0 && g->visited[j] == 0)
            {
                queue_enqueue(q, j);
                g->visited[j] = 1;
                printf("Vertex % d\n", j + 1);
            }
        }
    }
    queue_free(q);
}

void graph_free(struct graph *g)
{
    free(g->m);
    free(g->visited);
    free(g);
}

void graph_print(struct graph *g)
{
    int i, j;
    printf("Graph:\n");
    for (i = 0; i < g->nvertices; i++)
    {
        printf("Vertex %d: ", i + 1);
        for (j = 0; j < g->nvertices; j++)
        {
            if (g->m[i * g->nvertices + j] > 0)
            {
                printf("%d ", j + 1);
            }
        }
        printf("\n");
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define inf 99999999;
ShortestPathDijkstra(G, src, D, prev)
{
    int i = 0;
    while (V != src)
    { // Помещаем вершины в очередь с приоритетом
        D[i] = inf;
        prev[i] = -1;
        PriorityQueueInsert(Q, i, D[i]);
    }
    D[src] = 0;
    prev[src] = -1;
    PriorityQueueInsert(Q, src, D[src]);

    for
        i = 0 to n - 1 do
        {
            PriorityQueueExtractMin(Q); // Извлекаем узел, ближайший к начальному
                H = H +[v]// Отмечаем v как посещённый

for each
    u in Adj(v) \ H do
                { // Цикл по смежным непосещённым вершинам узла v
                    if (D[v] +
                            w(v, u) <
                        D[u])
                    {
                        then // Путь через u короче текущего пути?
                            D[u] = D[v] + w(v, u);
                        PriorityQueueDecreaseKey(Q, u, D[u]);
                        prev[u] = v;
                    }
                }
        }
}

int main()
{
}
/*int minDistance(int dist[], bool visited[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < Vershinigrap; v++)
    {
        if (!visited[v] && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

/*
void ShortestPathDijkstra(struct graph *graph, int src) {
    int distances[graph->nvertices];
    int previous[graph->nvertices];
    struct binary_heap *queue = create_heap(20); // Создаем кучу
    if (queue == NULL) {
        // Обработка ошибки создания кучи
        return;
    }

    for (int i = 0; i < graph->nvertices; i++) {
        if (i != src) {
            distances[i] = INT_MAX;
            previous[i] = -1;
            heap_insert(queue, i, distances[i]);
        }
    }

    distances[src] = 0;
    previous[src] = -1;
    heap_extract_min(queue);

    while (queue->nnodes > 0) {
        struct heapnode max_node = heap_extract_min(queue);
        int v = max_node.value;

        for (int i = 0; i < graph->nvertices; i++) {
            if (graph->edges[v][i].weight > 0) {
                int u = i;
                int alt = distances[v] + graph->edges[v][i].weight;
                if (alt < distances[u]) {
                    distances[u] = alt;
                    heap_decrease_key(queue, u, alt);
                    previous[u] = v;
                }
            }
        }
    }

    heap_free(queue); // Освобождаем память, выделенную для кучи
}*/

 // график 5 вершин из презентации
    /*g = graph_create(5);
    /*graph_set_edge(g, 1, 5, 100);
    graph_set_edge(g, 1, 2, 10);
    graph_set_edge(g, 1, 4, 30);
    graph_set_edge(g, 2, 3, 50);
    graph_set_edge(g, 3, 5, 10);
    graph_set_edge(g, 3, 4, 20);
    graph_set_edge(g, 4, 5, 60);8/


/*void dijkstra(struct graph *graph, int source,int capacity)
{
    int dist[graph->nvertices];
    int prev[graph->nvertices];

    struct binary_heap *heap = create_heap(capacity); // Создание пустой бинарной кучи

    // Инициализация массивов dist и prev
    for (int v = 0; v < graph->nvertices; v++) 
    {
        if (v != source)
        {
            dist[v] = INFINITY;  //1. Устанавливаем расстояние D[i] от начальной вершины s до всех остальных в ∞

            prev[v] = UNDEFINED;
        }
        else
        {
            dist[v] = 0; //Полагаем D[s] = 0
            prev[v] = UNDEFINED;
        }
    }
    

    // Добавление начальной вершины в бинарную кучу
    insert(heap, source, 0);

    // Основной цикл алгоритма Дейкстры
    while (!is_empty(heap)) //Помещаем все вершины в очередь с приоритетом Q (min-heap):
    {
        int u = extract_min(heap); 

        // Цикл для каждого соседа вершины u
        for (int v = 0; v < graph->nvertices; v++) //Извлекаем из очереди Q вершину v с минимальным приоритетом —ближайшую к s вершину
        {
            if (graph->m[u * graph->nvertices + v] > 0) //Возможно, пути из s через вершину v стали короче, выполняем проверку:
            {                                                           // Проверяем, смежны ли вершины u и v
                int alt = dist[u] + graph->m[u * graph->nvertices + v]; // Новая длина пути

                // Если новая длина пути короче текущей, обновляем информацию о вершине v
                if (alt < dist[v])
                {
                    dist[v] = alt;
                    prev[v] = u;

                    // Если вершина v уже есть в куче, уменьшаем её приоритет
                    if (contains(heap, v))
                    {
                        decrease_priority(heap, v, alt);
                    }
                    else
                    { // Иначе добавляем её в кучу
                        insert(heap, v, alt);
                    }
                }
            }
        }
    }

    // Вывод результатов
    printf("Vertex \t Distance \t Previous\n");
    for (int i = 0; i < graph->nvertices; i++)
    {
        printf("%d \t %d \t\t %d\n", i + 1, dist[i], prev[i] + 1);
    }

    // Освобождение памяти, занятой бинарной кучей
    destroy_heap(heap);
}*/
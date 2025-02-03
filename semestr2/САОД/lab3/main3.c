#include "queue_array.h"
#include "graph.h"
#include "binaryheap.h"
#define INFINITY INT_MAX
#define UNDEFINED -1
#define V 20




void dijkstra(struct graph *graph, int source,int capacity)
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
}

int main()
{
    srand(time(NULL));
    struct graph* g;
    int weight = rand() % 10+1;

    g = graph_create(30);
    // связный граф из 20 вершин
    /**/
    graph_set_edge(g, 1, 2, weight);
    graph_set_edge(g, 4, 1, weight);
    graph_set_edge(g, 3, 2, weight);
    graph_set_edge(g, 1, 5, weight);
    graph_set_edge(g, 2, 5, weight);
    graph_set_edge(g, 3, 5, weight);
    graph_set_edge(g, 3, 4, weight);
    graph_set_edge(g, 4, 5, weight);
    graph_set_edge(g, 3, 8, weight);
    graph_set_edge(g, 6, 7, weight);
    graph_set_edge(g, 7, 8, weight);
    graph_set_edge(g, 8, 9, weight);
    graph_set_edge(g, 8, 10, weight);
    graph_set_edge(g, 10, 11, weight);
    graph_set_edge(g, 9, 12, weight);
    graph_set_edge(g, 13, 11, weight);
    graph_set_edge(g, 13, 12, weight);
    graph_set_edge(g, 13, 14, weight);
    graph_set_edge(g, 14, 15, weight);
    graph_set_edge(g, 15, 17, weight);
    graph_set_edge(g, 15, 16, weight);
    graph_set_edge(g, 17, 19, weight);
    graph_set_edge(g, 16, 18, weight);
    graph_set_edge(g, 19, 20, weight);

    //printf("Graph representation:\n");
    //graph_print(g);
    /**/ 
    double timer1 = wtime();
    dijkstra(g, 0,20);

    //ShortestPathDijkstra(g,0);
    timer1 = wtime() - timer1;
    printf("Время работы алгоритма Дейкстры:  %.11f\n", timer1);

    // создание создания графа-решётки размером 100x100
    /**/
    struct graph* grid;
    grid = graph_create(100 * 100);

    for (int i = 1; i <= 100; i++)
    {
        for (int j = 1; j <= 100; j++)
        {
            int v = (i - 1) * 100 + j; // Получаем номер вершины по её координатам
            if (i > 1)
                graph_set_edge(grid, v, v - 100, weight); // Связываем с вершиной выше
            if (j > 1)
                graph_set_edge(grid, v, v - 1, weight); // Связываем с вершиной слева
        }
    }

   

    // алгоритм дейкстры для графа-решётки размером 100x100
    /*
    double timer2 = wtime();
    dijkstra(grid, 0,100*100);
    timer2 = wtime() - timer2;
    printf("Время работы алгоритма Дейкстры:  %f\n", timer2);*/



    
    /*
    printf("Graph representation:\n");
    graph_print(g);

    printf("BFS :\n");
    graph_bfs(g, 1);*/

    graph_free(g);
    graph_free(grid);
}
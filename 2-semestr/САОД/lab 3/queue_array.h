#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
struct queue
{
    int *a;
    int head;
    int tail;
    int size;
    int maxsize;
};

double wtime();
struct queue *queue_create(int maxsize);
void queue_free(struct queue *q);
int queue_size(struct queue *q);
int queue_enqueue(struct queue *q, int value);
int queue_dequeue(struct queue *q);
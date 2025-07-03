#include <stdio.h>
#include <bool.h>

typedef struct {
    int front;
    int rear;
    int size;
    int *item;
} Queue

void queue_init (Queue *queue, int size) {
    queue -> front = -1;
    queue -> rear = -1;
    queue -> size = size;
    queue -> item = (int*)malloc(sizeof(int)*size);
}

bool isEmpty(Queue *queue) {
    return queue->front == -1 || queue -> front > queue -> rear;
}


bool isFull(Queue *queue) {
    return queue->rear == (queue -> size) - 1;
}

void enqueue(Queue *queue, int item){
    if (isEmpty(queue)) {
        queue -> front = 0;
        queue -> rear = 0;
        queue -> item[queue -> rear] = item;
    } else if(isFull(queue)) {
        printf("Queue is full\n");
    } else {
        ++queue -> rear;
        queue -> item[queue -> rear] = item;
    }
}

void dequeue (Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
    } else {
        queue -> itemm[queue -> front] = 0;
        free(queue -> item[queue -> front]);
        --queue -> front;
    }
    
}

int get_front(Queue *queue){
    return queue -> item[0];
}

int get_rear(Queue *queue){
    return queue -> item[size - 1];
}
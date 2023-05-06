#include <stdlib.h>
#include <stdio.h>

#define MAX_QUEUE_SIZE 10

typedef struct queue{
    int current_size;
    int head;//dequeue
    int tail;//enqueue
    int items[MAX_QUEUE_SIZE];
}queue;

queue* create_queue(){
    queue* new_queue = (queue*) malloc(sizeof(queue));
    new_queue->current_size = 0;
    new_queue->head = 0;
    new_queue->tail = MAX_QUEUE_SIZE - 1;

    return new_queue;
}

int is_empty(queue *queue){
    return (queue->current_size == 0);
}

void enqueue(queue *queue, int item){
    if(queue->current_size >= MAX_QUEUE_SIZE)
    {
        printf("queue overflow");
    }else
    {
        queue->tail = (queue->tail + 1) % MAX_QUEUE_SIZE; //setando o indice no array
        queue->items[queue->tail] = item;
        queue->current_size++;
    }

    return;
}

int dequeue(queue *queue){
    if(is_empty(queue))
    {
        printf("queue under_flow");
        return -1;
    }else
    {
        int dequeued = queue->items[queue->head];
        queue->head = (queue->head + 1) % MAX_QUEUE_SIZE;
        queue->current_size--;
        //printf("[%d]\n",queue->current_size);
        return dequeued;
    }
    
}

void print_queue(queue *queue){
    int c  = queue->head;
    while(c <= queue->tail && !is_empty(queue)){
        printf("%d ",queue->items[c]);
        c++;
    }
    printf("\n");
    return;
}

int main(){
    printf("hi\n");

    queue *fila = create_queue();
    
    enqueue(fila,8);
    enqueue(fila,3);
    enqueue(fila,4);
    print_queue(fila);
    dequeue(fila);
    print_queue(fila);
    
    
    
    
}
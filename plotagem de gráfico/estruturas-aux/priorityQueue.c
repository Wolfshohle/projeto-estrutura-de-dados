#include <stdlib.h>
#include <stdio.h>

typedef struct queueNode{
    int item;
    int priority;
    struct queueNode *next;
}queueNode;

typedef struct priorityQueue{
    queueNode *head;
}priorityQueue;

priorityQueue* createPriorityQueue(){
    priorityQueue *new_node = (priorityQueue*) malloc(sizeof(priorityQueue));

    new_node->head = NULL;
    return new_node;
}

int isEmpty(priorityQueue* pq){
    return (pq->head == NULL);
}   

void enqueue(priorityQueue *pq,int item, int prio){
    queueNode *new_node = (queueNode*) malloc(sizeof(queueNode));
    new_node->item = item;
    new_node->priority = prio;

    if(isEmpty(pq) || prio > pq->head->priority){
        new_node->next = pq->head;
        pq->head = new_node;
    }else
    {
        queueNode* current = pq->head;
        while(current->next != NULL && current->next->priority > prio){
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    return;

}

queueNode* dequeue(priorityQueue* pq){
    if(isEmpty(pq)){
        printf("Priority queue is empty\n");
        return NULL;
    } else{
        queueNode* node = pq->head;
        pq->head = pq->head->next;
        node->next = NULL;
        return node; //dequed node
    }
    
}

void print_pq(priorityQueue *pq){
    queueNode *current = pq->head;
    while (current != NULL)
    {
        printf("(%d,%d);\n",current->item,current->priority);
        current = current->next;
    }
    
}

int main(){
    priorityQueue *fila_pq = createPriorityQueue();
    printf("%d\n",isEmpty(fila_pq));

    enqueue(fila_pq,2,8);
    enqueue(fila_pq,11,3);
    enqueue(fila_pq,1,4);
    enqueue(fila_pq,3,0);
    print_pq(fila_pq);
    printf("%d\n",isEmpty(fila_pq));

    queueNode* dequeued;

    dequeued = dequeue(fila_pq);
    printf("[i:%d,p:%d]\n",dequeued->item,dequeued->priority);
    print_pq(fila_pq);

}
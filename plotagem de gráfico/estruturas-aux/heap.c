#include <stdlib.h>
#include <stdio.h>

#define MAX_HEAP_SIZE 20

typedef struct heap{
    int size;
    int items[MAX_HEAP_SIZE];
}heap;

heap *create_heap(){
    heap *new_heap = (heap*) malloc(sizeof(heap)); 
    new_heap->size = 0;
    return new_heap;
}

int get_parent_index(heap *heap,int index){
    return index/2;
}

int get_left_index(heap *heap,int index){
    return index*2;
}

int get_right_index(heap *heap,int index){
    return index*2+1;
}

int item_of(heap *heap,int index){
    return heap->items[index];
}

void swap(int *a,int *b){
    int c = *a;
    *a = *b;
    *b = c;
    return;

}

void enqueue(heap *heapao,int data){
    if(heapao->size >= MAX_HEAP_SIZE){
        printf("Heap overflow\n");
    }else
    {
        heapao->items[++heapao->size] = data;
        int key_index = heapao->size;
        int parent_index= get_parent_index(heapao,heapao->size);

        //equanto nao chegar a raiz e  equanto este ser maior que o pai
        while (parent_index >= 1 && 
                heapao->items[key_index] > heapao->items[parent_index])
        {
            swap(&heapao->items[key_index],&heapao->items[parent_index]);

            //atualizar os "status" do antigo nó pai agora trocado como filho;
            key_index = parent_index;
            parent_index = get_parent_index(heapao,key_index);

        }
        
    }
    return;
} 

void print_heap_tree_like(heap *heap){
    int size_heap = heap->size;
    int i,level = 1;
    int level_size = 1;
    for(i = 1; i <= size_heap; i++){
        if(i == level_size){
            printf("\nLevel %d:",level);
            level_size = level_size*2;
            level++;
        }
        printf("%d ",heap->items[i]);
    }

    return;
}

int heap_is_empty(heap *heapao){
    return (heapao->size == 0);
}


//pegue o elemento em root, subtiuia pelo elemento no ultimo no e diminua o tamanho da queue

int main(){
    heap *heapao = create_heap();


   
    /*
    enqueue(heapao,16);
    enqueue(heapao,12);
    enqueue(heapao,13);
    print_heap_tree_like(heapao);
    enqueue(heapao,20);
    printf("\n-----\n");
    print_heap_tree_like(heapao);
    */
}
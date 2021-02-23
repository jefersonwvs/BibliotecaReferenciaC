#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 5

typedef struct queue* Queue;
struct queue {
    int first;
    int data[MAX_SIZE]; // static allocation
    int last;
    int size;
};

void init(Queue);
int isEmpty(Queue);
int isFull(Queue);
int enqueue(Queue, int);
int dequeue(Queue);
int first(Queue);
void close(Queue);
void display(Queue);

int main()
{
    struct queue aux; // static allocation
    Queue Q = &aux;
    init(Q);

    int i;

    for(i = 1; i <= 6; i++){
        enqueue(Q, i);
        display(Q);
    }

    for(i = 1; i <= 6; i++){
        dequeue(Q);
        display(Q);
    }

    printf("%d, %d, %d\n", Q->first, Q->last, Q->size);

    enqueue(Q, 94);
    enqueue(Q, 43);
    display(Q);
    printf("First: %d\n", first(Q));

    printf("%d, %d, %d\n", Q->first, Q->last, Q->size);

    close(Q);   // static "deallocation"
    
    system("pause");
    return EXIT_SUCCESS;
}

void init(Queue Q) {
    Q->first = -1;
    Q->last = -1;
    Q->size = 0;
}

int isEmpty(Queue Q) {
    return !Q->size;
}

int isFull(Queue Q) {
    return Q->size == MAX_SIZE;
}

int enqueue(Queue Q, int data) {
    if (!isFull(Q)) {
        if (isEmpty(Q))
            Q->first++;
        Q->last++;
        Q->data[Q->last] = data;
        Q->size++;
        return 1;
    }
}

int dequeue(Queue Q) {
    int i, deleted;
    if (!isEmpty(Q)) {
        deleted = Q->data[Q->first];
        for (i = 0; i <= Q->last-1; i++)
            Q->data[i] = Q->data[i+1];
        Q->data[Q->last] = -1;
        Q->last--;
        Q->size--;
        if (isEmpty(Q))
            Q->first = -1;
        return deleted;
    }
    return -1;
}

int first(Queue Q) {
    return !isEmpty(Q) ? Q->data[Q->first] : -1;
}

void close(Queue Q) {
    while(!isEmpty(Q))
        dequeue(Q);
}

void display(Queue Q) {
    int i;
    for (i = 0; i < Q->size; i++)
        printf("<<--[%d]", Q->data[i]);
    printf("\n");
}

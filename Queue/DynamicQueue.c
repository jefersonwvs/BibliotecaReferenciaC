#include <stdio.h>
#include <stdlib.h>

typedef struct cell* Cell;
struct cell {
    int data;
    Cell next;
};

typedef struct queue* Queue;
struct queue {
    Cell first;
    Cell last;
    int size;
};

Queue init();
void* close(Queue);
int isEmpty(Queue);
Cell createsCell(int);
void enqueue(Queue, int);
void display(Queue);
int dequeue(Queue);

int main() {

    Queue Q = init();

    if (Q == NULL) { // defensive programming
        printf("Error: the required memory could not be allocated!\n");
        system("pause");
        return EXIT_FAILURE;
    }

    // printf("%p, %p, %d\n", Q->first, Q->last, Q->size);
    // printf("%d\n", isEmpty(Q));

    enqueue(Q, 5);
    display(Q);
    enqueue(Q, 15);
    display(Q);
    enqueue(Q, 3);
    display(Q);
    enqueue(Q, 0);
    display(Q);
    enqueue(Q, -7);
    display(Q);

    printf("0x%p, 0x%p, %d\n", Q->first, Q->last, Q->size);


    dequeue(Q);
    display(Q);
    dequeue(Q);
    display(Q);
    dequeue(Q);
    display(Q);
    dequeue(Q);
    display(Q);
    printf("0x%p, 0x%p, %d\n", Q->first, Q->last, Q->size);

    Q = close(Q);

    return EXIT_SUCCESS;
}

Queue init() {
    Queue Q = NULL;
    if ((Q = (Queue)malloc(sizeof(struct queue))) != NULL) { // the comparison with NULL is not necessary
        Q->first = NULL;
        Q->last = NULL;
        Q->size = 0;
    }
    return Q;
}

void* close(Queue Q) {
    while(!isEmpty(Q))
        dequeue(Q);
    free(Q);
    return NULL;
}

int isEmpty(Queue Q) {
    return !Q->size;
}

Cell createsCell(int data) {
    Cell newCell = NULL;
    if ((newCell = (Cell)malloc(sizeof(struct cell)))) {
        newCell->data = data;
        newCell->next = NULL;
    }
    return newCell;
}

void enqueue(Queue Q, int data) {
    Cell newCell;
    if (newCell = createsCell(data)) {
        if (isEmpty(Q)) {
            Q->first = newCell;
            Q->last = newCell;
        } else {
            Q->last->next = newCell;
            Q->last = newCell;
        }
        Q->size++;
    }
}

void display(Queue Q) {
    Cell aux = Q->first;
    while (aux) {
        printf("<<---[%3d]", aux->data);
        aux = aux->next;
    }
    printf("\n");
}

int dequeue(Queue Q) {
    Cell deleted = NULL;
    int data;
    if (!isEmpty(Q)) {
        deleted = Q->first;
        Q->first = deleted->next;
        Q->size--;
        data = deleted->data;
        free(deleted);
        if (isEmpty(Q))
            Q->last = NULL;
        return data;
    }
    return -1;
}

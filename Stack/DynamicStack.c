#include <stdio.h>
#include <stdlib.h>

typedef struct cell* Cell;
struct cell {
    int data;
    Cell next;
};

typedef struct stack* Stack;
struct stack {
    Cell top;
    int size;
};

Stack init();
int isEmpty(Stack);
Cell createsCell(int);
int push(Stack, int);
int pop(Stack);
int top(Stack);
void* close(Stack);
void display(Stack);

int main()
{
    Stack S = init(); // dinamic allocation

    if (S == NULL) { // defensive programming
        printf("Error: the required memory could not be allocated!\n");
        system("pause");
        return EXIT_FAILURE;
    }

    printf("Top: %p - Size: %d\n\n", S->top, S->size);

    push(S, 5);
    display(S);
    push(S, 4);
    display(S);
    push(S, 2);
    display(S);
    printf("%d\n", top(S));

    /*pop(S);
    display(S);
        pop(S);
    display(S);
        pop(S);
    display(S);
        pop(S);
    display(S);
    */

    S = close(S); // dynamic deallocation

    return EXIT_SUCCESS;
}

Stack init() {
    Stack S = NULL;
    if ((S = (Stack)malloc(sizeof(struct stack))) != NULL) { // the comparison with NULL is not necessary
        S->top = NULL;
        S->size = 0;
    }
    return S;
}

int isEmpty(Stack S) {
    return !S->size;
}

Cell createsCell(int data) {
    Cell newCell = NULL;
    if ((newCell = (Cell)malloc(sizeof(struct cell)))) {
        newCell->data = data;
        newCell->next = NULL;
    }
    return newCell;
}

int push(Stack S, int data) {
    Cell newCell = createsCell(data);
    if (newCell == NULL)
        return 0;
    newCell->next = S->top;
    S->top = newCell;
    S->size++;
    return 1;
}

int pop(Stack S) {
    Cell deleted = NULL;
    int data;
    if (!isEmpty(S)) {
        deleted = S->top;
        S->top = deleted->next;
        S->size--;
        data = deleted->data;
        free(deleted);
        return data;
    }
    return -1;
}

int top(Stack S) {
    return (!isEmpty(S) ? S->top->data : -1);
}

void* close(Stack S) {
    while(!isEmpty(S))
        pop(S);
    free(S);
    return NULL;
}

void display(Stack S) {
    Cell aux = S->top;
    while (aux) {
        printf("[ %d ]\n", aux->data);
        aux = aux->next;
    }
    printf("\n");
}

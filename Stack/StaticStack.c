#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 5

typedef struct stack* Stack;
struct stack {
    int data[MAX_SIZE]; // static allocation
    int top;
    int size;
};

void init(Stack);
int isEmpty(Stack);
int isFull(Stack);
int push(Stack, int);
int pop(Stack);
void display(Stack);
int top(Stack);
void close(Stack);

int main()
{
    struct stack aux; // static allocation
    Stack S = &aux;
    init(S);

    int i;

    for (i = 1; i <= 7; i++) {
        push(S, i);
        display(S);
        printf("\n");
    }

    printf("%d\n", top(S));
    /*printf("\n");

    for (i = 1; i <= 7; i++) {
        pop(&S);
        display(&S);
        printf("\n");
    }*/

    printf("%d\n", S->top);

    close(S); // static "deallocation"
    
    system("pause");
    return EXIT_SUCCESS;

}

void init(Stack S) {
    S->top = -1;
    S->size = 0;
}

int isEmpty(Stack S) {
    return !(S->size);     // if S->size == 0, returns 1; else, returns 0;
}

int isFull(Stack S) {
    return S->size == MAX_SIZE;
}

int push(Stack S, int info) {
    if (!isFull(S)) {
        S->top++;
        S->data[S->top] = info;
        S->size++;
        return 1;
    }
    return 0;
}

int pop(Stack S) {
    if (!isEmpty(S)) {
        S->data[S->top] = -1;   // -1 indicates available position
        S->top--;
        S->size--;
        return 1;
    }
    return 0;
}

int top(Stack S) {
    return !isEmpty(S) ? S->data[S->top] : -1;
}

void close(Stack S) {
    while (!isEmpty(S))
        pop(S);
}

void display(Stack S) {
    int i;
    for (i = S->top; i >= 0; i--) {
        printf("[ %2d ]\n", S->data[i]);
    }
}

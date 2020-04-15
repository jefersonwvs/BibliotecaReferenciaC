#include <stdlib.h>
#include <stdio.h>

#define TAM_MAX 5

struct fila {
    int primeiro;
    int V[TAM_MAX];
    int ultimo;
    int tamanho;
};
typedef struct fila Fila;

void inicializarFila(Fila*);
int filaVazia(Fila*);
int filaCheia(Fila*);
int enfileirar(Fila*, int);
int desenfileirar(Fila*);
int primeiroFila(Fila*);
void finalizarFila(Fila*);
void imprimeFila(Fila*);

int main() {

    Fila F;
    int i;

    inicializarFila(&F);
    for(i = 1; i <= 6; i++){
        enfileirar(&F, i);
        imprimeFila(&F);
    }

    for(i = 1; i <= 6; i++){
        desenfileirar(&F);
        imprimeFila(&F);
    }

    printf("%d, %d, %d\n", F.primeiro, F.ultimo, F.tamanho);

    enfileirar(&F, 94);
    enfileirar(&F, 43);
    imprimeFila(&F);
    printf("primeiro elemento da fila: %d\n", primeiroFila(&F));

    //finalizarFila(&F);
    printf("\n%d, %d, %d\n", F.primeiro, F.ultimo, F.tamanho);



    return 0;
}

void inicializarFila(Fila *F) {
    F->primeiro = -1;
    F->ultimo = -1;
    F->tamanho = 0;
}

int filaVazia(Fila *F) {
    return !F->tamanho;
}

int filaCheia(Fila *F) {
    if (F->tamanho == TAM_MAX)
        return 1;
    return 0;
}

int enfileirar(Fila *F, int x) {
    if (!filaCheia(F)) {
        if (filaVazia(F))
            F->primeiro++;
        F->ultimo++;
        F->V[F->ultimo] = x;
        F->tamanho++;
        return 1;
    }
}

int desenfileirar(Fila *F) {
    int i, x;
    if (!filaVazia(F)) {
        x = F->V[0];                // guardando o elemento desenfileirado
        for (i = 0; i <= F->ultimo-1; i++)
            F->V[i] = F->V[i+1];    // os elementos vão tomando o lugar daquele que saiu, como numa fila de espera comum
        F->V[F->ultimo] = -1;       // a posição do último da fila está vaga
        F->ultimo--;                // o último está, agora, uma posição à frente
        F->tamanho--;
        if (filaVazia(F))
            F->primeiro = -1;
        return x;
    }
    return -1;      // convenção para quando não desenfileirado
}

int primeiroFila(Fila* F) {
    if (!filaVazia(F))
        return F->V[0];
    return -1;
}

void finalizarFila(Fila *F) {
    while(!filaVazia(F))
        desenfileirar(F);
}

void imprimeFila(Fila* F) {
    int i;
    for (i = 0; i <= F->ultimo; i++)
        printf("<<--[%d]", F->V[i]);
    printf("\n");
}

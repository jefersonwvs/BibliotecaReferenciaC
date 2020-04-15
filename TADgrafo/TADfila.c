#include <stdio.h>
#include <stdlib.h>

struct celula { // celula == no
    int vertice;
    struct celula* proxAdj;
};
typedef struct celula celula;

struct fila {
    struct celula* primeiro;
    struct celula* ultimo;
    int tamanho;
};
typedef struct fila Fila;


void inicializarFila(Fila* F) {
    F->primeiro = NULL;
    F->ultimo = NULL;
    F->tamanho = 0;
}

int filaVazia(Fila* F) {
   return !F->tamanho;  //se F->tamanho == 0: retorna 1, senão retorna 0;
}

celula* criaCelula(int vertAdj) {
    celula* novaCelula;
    if ((novaCelula = malloc(sizeof(celula)))) {
        novaCelula->vertice = vertAdj;
        novaCelula->proxAdj = NULL;
        return novaCelula;
    }
    return NULL;
}

int enfileirar(Fila* F, int novoRotulo) {
    celula* novaCelula;
    if ((novaCelula = criaCelula(novoRotulo))) {
        if (filaVazia(F))
            F->primeiro = novaCelula;
        else
            F->ultimo->proxAdj = novaCelula;
        F->ultimo = novaCelula;
        F->tamanho++;
        return 1;   //elemento enfileirado
    }
    return 0;   //elemento não enfileirado.
}

void imprimeFila(Fila* F) {
    celula* aux = F->primeiro;
    while (aux) {
        printf("-->[%d]", aux->vertice);
        aux = aux->proxAdj;
    }
    printf("\n");
}

int desenfileirar(Fila* F) {
    celula* removido;
    int x;
    if (!filaVazia(F)) {
        removido = F->primeiro;
        F->primeiro = removido->proxAdj;
        F->tamanho--;
        x = removido->vertice;
        free(removido);
        if (filaVazia(F))
            F->ultimo = NULL;
        return x;
    }
    return -1;
}

void finalizarFila(Fila* F) {
    while(!filaVazia(F))
        desenfileirar(F);
}

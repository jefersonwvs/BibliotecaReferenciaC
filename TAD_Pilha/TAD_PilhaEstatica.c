#include <stdlib.h>
#include <stdio.h>

#define TAM_MAX 5

struct pilha {
    int V[TAM_MAX];
    int topo;
    int tamanho;
};
typedef struct pilha Pilha;

void inicializaPilha(Pilha*);
int pilhaVazia(Pilha*);
int pilhaCheia(Pilha*);
int empilha(Pilha*, int);
int desempilha(Pilha*);
void imprimePilha(Pilha*);

int main() {

    Pilha P;
    int i;

    inicializaPilha(&P);

    for (i = 1; i <= 7; i++) {
        empilha(&P, i);
        imprimePilha(&P);
        printf("\n");
    }

    printf("%d\n", topoPilha(&P));
    /*printf("\n");

    for (i = 1; i <= 7; i++) {
        desempilha(&P);
        imprimePilha(&P);
        printf("\n");
    }*/

    finalizaPilha(&P);
    printf("%d\n", P.topo);

    system("pause");

    return 0;

}

void inicializaPilha(Pilha *P) {
    P->topo = -1;
    P->tamanho = 0;
}

int pilhaVazia(Pilha *P) {
    return !P->tamanho;     //if P->tamanho == 0, retorna1; senão, retorna 0;
}

int pilhaCheia(Pilha *P) {
    if (P->tamanho == TAM_MAX)
        return 1;
    return 0;
}

int empilha(Pilha *P, int x) {
    if (!pilhaCheia(P)) {
        P->topo++;          //mudando o topo
        P->V[P->topo] = x;  //empilhando
        P->tamanho++;       //aumentando o tamanho
        return 1;
    }
    return 0;
}

int desempilha(Pilha *P) {  //n�o retorna o elemento desempilhado
    if (!pilhaVazia(P)) {
        P->V[P->topo] = -1;     //-1 � a marca��o para exclu�do
        P->topo--;
        P->tamanho--;
        return 1;
    }
    return 0;
}

int topoPilha(Pilha *P) {
    if (!pilhaVazia(P))
        return P->V[P->topo];
    return -1;
}

void finalizaPilha(Pilha *P) {
    while (!pilhaVazia(P))
        desempilha(P);
}

void imprimePilha(Pilha *P) {
    int i;
    for (i = P->topo; i >= 0; i--) {
        printf("[ %2d ]\n", P->V[i]);
    }
}

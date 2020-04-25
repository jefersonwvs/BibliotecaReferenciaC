#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vertice {
    struct vertice* esq;
    int chave;
    struct vertice* dir;
};
typedef struct vertice Vertice;
typedef struct vertice* ArvBinPesq;    // �rvore Bin�ria de Pesquisa;

int arvoreVazia(ArvBinPesq*);
ArvBinPesq criaVertice(int);
int insereVertice(ArvBinPesq*, int);
int removeVertice(ArvBinPesq*, int);
ArvBinPesq antecessorVertice(ArvBinPesq*);
int buscaVertice(ArvBinPesq*, int);
void preOrdem(ArvBinPesq);
void emOrdem(ArvBinPesq);
void posOrdem(ArvBinPesq);
void representacaoAninhada(ArvBinPesq);
void representacaoIndentada(ArvBinPesq, int);
void construtor(ArvBinPesq*, char*);

int main() {

    ArvBinPesq Raiz = NULL;

    char *arvore = "5(3(2(1),4), 7(6,8(,9)))";

    printf("%p\n", Raiz);
    printf("%d\n\n", arvoreVazia(&Raiz));

    /*insereVertice(&Raiz, 4);
    insereVertice(&Raiz, 2);
    insereVertice(&Raiz, 1);
    insereVertice(&Raiz, 3);
    insereVertice(&Raiz, 6);
    insereVertice(&Raiz, 5);
    insereVertice(&Raiz, 7);*/

    construtor(&Raiz, arvore);

    printf("\n\n");
    representacaoAninhada(Raiz);
    printf("\n\n");

    printf("\n\n");
    representacaoIndentada(Raiz, 0);
    printf("\n\n");

    printf("preOrdem: ");
    preOrdem(Raiz);
    printf("\nemOrdem: ");
    emOrdem(Raiz);
    printf("\nposOrdem: ");
    posOrdem(Raiz);
    printf("\n\n");

    removeVertice(&Raiz, 4);
    removeVertice(&Raiz, 6);
    removeVertice(&Raiz, 5);
    removeVertice(&Raiz, 3);
    removeVertice(&Raiz, 2);
    removeVertice(&Raiz, 1);
    removeVertice(&Raiz, 7);
    /*insereVertice(&Raiz, 53);
    insereVertice(&Raiz, 21);
    insereVertice(&Raiz, 79);*/
    printf("preOrdem: ");
    preOrdem(Raiz);
    printf("\nemOrdem: ");
    emOrdem(Raiz);
    printf("\nposOrdem: ");
    posOrdem(Raiz);
    printf("\n\n");

    printf("\n%p\n", Raiz);
    printf("%d\n", buscaVertice(&Raiz, 4));
    printf("%d\n", buscaVertice(&Raiz, 8));

    system("pause");
    return 0;
}

int arvoreVazia(ArvBinPesq* ptrRaiz) {
    return *ptrRaiz == NULL;
}

ArvBinPesq criaVertice(int x) {
    ArvBinPesq novoVertice;
    if(novoVertice = (ArvBinPesq)malloc(sizeof(Vertice))) {
        novoVertice->esq = NULL;
        novoVertice->chave = x;
        novoVertice->dir = NULL;
        return novoVertice;
    }
    return NULL;
}

int insereVertice(ArvBinPesq* ptrRaiz, int x) { // [ptrRaiz]----->[Raiz]----->...
    ArvBinPesq aux;                             //                [aux]----->
    aux = *ptrRaiz;                             //                [aux]----->...
    if (arvoreVazia(&aux)) {                    //     se         [aux]----->\ .
        aux = criaVertice(x);                   //                [aux]----->[\|x|\]
        *ptrRaiz = aux;                         // [ptrRaiz]----->[Raiz]---->[\|x|\]
        return 1;
    } else {
        if (x < aux->chave)
            return insereVertice(&(aux->esq), x);
        else {
            if (x == aux->chave)                // chave já existente n�o pode inserir
                return 0;
            else    // (x > aux->chave)
                return insereVertice(&(aux->dir), x);
        }
    }
}

int removeVertice(ArvBinPesq* ptrRaiz, int x){
    ArvBinPesq aux; //aux: vértice que será removido

    if (*ptrRaiz == NULL)   // árvore nula ou elemento a ser removido não está na árvore
        return 0;

    if (x == (*ptrRaiz)->chave) {  // vértice encontrado! A remover ...
        aux = *ptrRaiz; // aux aponta para a Raiz atual, que é o vértice a ser removido
        if ((*ptrRaiz)->dir == NULL) {  // vértice de grau 0, ou de grau 1, com sub-arvore esquerda
            *ptrRaiz = (*ptrRaiz)->esq; // Raiz atual (vértice que será removido) passa a apontar para sua única sub-árvore, neste caso, a esquerda. No caso de grau 0, a sub-árvore esquerda também será nula, o que fará com que a árvore final seja nula (vazia)
        } else {
            if ( (*ptrRaiz)->esq == NULL)   // vértice de grau 1, com sub-árvore direita
                *ptrRaiz = (*ptrRaiz)->dir; // Raiz atual (vértice que será removido) passa a apontar para sua única sub-árvore, neste caso, a direita
            else {  /* remoção através da troca de posição entre o elemento a ser eliminado e seu antecessor */
                aux = antecessorVertice(&(aux->esq));   // "isola" o antecessor para ser eliminado
                (*ptrRaiz)->chave = aux->chave; // coloca a chave do antecessor na raiz da árvore ou sub-árvore
            }
        }
        free(aux);  // libera a memória
        return 1;

    } else {
        if (x < (*ptrRaiz)->chave) // vértice a ser removido é menor do que a raiz da árvore ou da subárvore
            return removeVertice(&((*ptrRaiz)->esq), x);
        else // (aux->chave < x) vértice a ser removido é maior do que a raiz da árvore ou da subárvore
            return removeVertice(&((*ptrRaiz)->dir), x);
    }
}

ArvBinPesq antecessorVertice(ArvBinPesq* ptrRaiz) {
    ArvBinPesq aux = *ptrRaiz;
    if (!aux->dir) { // se aux->dir é nulo, então aux é o antecessor
        *ptrRaiz = (*ptrRaiz)->esq;
        return aux;
    } else
        return antecessorVertice(&(aux->dir));
}

int buscaVertice(ArvBinPesq* ptrRaiz, int x) {
    ArvBinPesq aux = *ptrRaiz;
    if (aux) {
        if (x < aux->chave)
            return buscaVertice(&aux->esq, x);
        else {
            if (x == aux->chave)
                return 1;
            else
                return buscaVertice(&aux->dir, x);
        }
    }
    return 0;
}

void preOrdem(ArvBinPesq ptrRaiz) {
    ArvBinPesq aux = ptrRaiz;
    if (aux) {
        printf("%d  ", aux->chave);
        preOrdem(aux->esq);
        preOrdem(aux->dir);
    }
}

void emOrdem(ArvBinPesq ptrRaiz) {
    ArvBinPesq aux = ptrRaiz;
    if (aux) {
        emOrdem(aux->esq);
        printf("%d  ", aux->chave);
        emOrdem(aux->dir);
    }
}

void posOrdem(ArvBinPesq ptrRaiz) {
    ArvBinPesq aux = ptrRaiz;
    if (aux) {
        posOrdem(aux->esq);
        posOrdem(aux->dir);
        printf("%d  ", aux->chave);
    }
}

void representacaoAninhada(ArvBinPesq ptrRaiz) {
    ArvBinPesq aux = ptrRaiz;
    if (aux) {
        printf("%d", aux->chave);
        if (aux->esq || aux->dir) {
            printf("(");
            representacaoAninhada(aux->esq);
            if (aux->dir){
                printf(",");
                representacaoAninhada(aux->dir);
            }
            printf(")");
        }
    }
}

void representacaoIndentada(ArvBinPesq ptrRaiz, int tabs) {
    ArvBinPesq aux = ptrRaiz;
    int i;
    if (aux == NULL)
        return;
    for(i = 0; i < tabs; i++)
        printf("  ");
    printf("%d\n", aux->chave);
    representacaoIndentada(aux->esq, tabs+1);
    representacaoIndentada(aux->dir, tabs+1);

}

void construtor(ArvBinPesq* ptrRaiz, char* arvore) {
    int i, x;
    int tam = strlen(arvore);
    for(i = 0; i < tam; i++) {
        if ( (arvore[i] != '(' && arvore[i] != ')') && (arvore[i] != ',' && arvore[i] != ' ') ){
            x = arvore[i] % 48; // transforma char em int. !válido SOMENTE para chaves de 0 a 9, pois a partir daí os números têm mais de 1 caractere
            insereVertice(ptrRaiz, x);
        }
    }
}

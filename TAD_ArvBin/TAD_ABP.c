#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vertice {
    struct vertice* esq;
    int chave;
    struct vertice* dir;
};
typedef struct vertice Vertice;
typedef struct vertice* ArvBinPesq;    // Árvore Binária de Pesquisa;

int arvoreVazia(ArvBinPesq*);
ArvBinPesq criaVertice(int);
int insereVertice(ArvBinPesq*, int);
int removeVertice(ArvBinPesq*, int);
ArvBinPesq antecessorVertice(ArvBinPesq*);
ArvBinPesq sucessorVertice(ArvBinPesq*);
int buscaVertice(ArvBinPesq*, int);
void preOrdem(ArvBinPesq);
void emOrdem(ArvBinPesq);
void posOrdem(ArvBinPesq);
void representacaoAninhada(ArvBinPesq);
void representacaoIndentada(ArvBinPesq, int);
void constroiArvore(ArvBinPesq*, char*);
void concatenarCaractere(char*, char);
void destroiArvore(ArvBinPesq*);
int giraVertice(ArvBinPesq*, int, int);
int rotacaoEsquerda(ArvBinPesq*);
int rotacaoDireita(ArvBinPesq*);

int main() {

    ArvBinPesq Raiz = NULL;

    char *arvore = "50(30(20(10),40), 70(60,80(,90)))";

    printf("====================Arvore Binaria de Pesquisa - ABP====================\n");

    constroiArvore(&Raiz, arvore);
    /*insereVertice(&Raiz, 51);
    insereVertice(&Raiz, 52);
    insereVertice(&Raiz, 53);*/
    //destroiArvore(&Raiz);
    printf("\nRepresentacao aninhada: ");
    representacaoAninhada(Raiz);

    printf("\nRepresentacao indentada: \n");
    representacaoIndentada(Raiz, 0);
    printf("\n");

    printf("Percursos:");
    printf("\n  PreOrdem: ");
    preOrdem(Raiz);
    printf("\n  InOrdem: ");
    emOrdem(Raiz);
    printf("\n  PosOrdem: ");
    posOrdem(Raiz);
    printf("\n");

    /*giraVertice(&Raiz, 51, 1);
    representacaoAninhada(Raiz);
    printf("\n");
    insereVertice(&Raiz, 55);
    representacaoAninhada(Raiz);
    printf("\n");*/

    printf("========================================================================\n\n");

    /*removeVertice(&Raiz, 4);
    removeVertice(&Raiz, 6);
    removeVertice(&Raiz, 5);
    removeVertice(&Raiz, 3);
    removeVertice(&Raiz, 2);
    removeVertice(&Raiz, 1);
    removeVertice(&Raiz, 7);
    insereVertice(&Raiz, 53);
    insereVertice(&Raiz, 21);
    insereVertice(&Raiz, 79);*/

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

ArvBinPesq sucessorVertice(ArvBinPesq* ptrRaiz) {
    ArvBinPesq aux = *ptrRaiz;
    if (!aux->esq) {
        *ptrRaiz = (*ptrRaiz)->dir;
        return aux;
    } else
        return sucessorVertice(&(aux->esq));
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

void constroiArvore(ArvBinPesq* ptrRaiz, char* arvore) {
    int i, j, x;
    int tam = strlen(arvore);
    char aux[5] = "";
    for(i = 0; i < tam; i++) {
        strcpy(aux, "");
        while ( (((arvore[i] != '(' && arvore[i] != ')') && arvore[i] != ',') && arvore[i] != ' ') && arvore[i] != '\0'){
            concatenarCaractere(aux, arvore[i]);
            i++;
        }
        if (strlen(aux) > 0) {
            x = atoi(aux);
            insereVertice(ptrRaiz, x);
        }
    }
}

void concatenarCaractere(char* palavra, char caractere) {
    int tam = strlen(palavra);
    palavra[tam] = caractere;
    palavra[tam+1] = '\0';
}

void destroiArvore(ArvBinPesq* ptrRaiz) {
    ArvBinPesq aux = *ptrRaiz;
    if (aux != NULL) {
        destroiArvore(&aux->esq);
        destroiArvore(&aux->dir);
        free(aux);
        *ptrRaiz = NULL;
    }
}

int giraVertice(ArvBinPesq* ptrRaiz, int x, int sent) {
    if (*ptrRaiz != NULL) {
        if ((*ptrRaiz)->chave == x) {   // vertice a ser rotacionado foi encontrado
            if (sent > 0)
                rotacaoEsquerda(ptrRaiz);
            else
                rotacaoDireita(ptrRaiz);
        } else {
            if (x < (*ptrRaiz)->chave)
                giraVertice(&(*ptrRaiz)->esq, x, sent);
            else
                giraVertice(&(*ptrRaiz)->dir, x, sent);
        }
    } else
        return 0;
}

int rotacaoEsquerda(ArvBinPesq* V) {
    ArvBinPesq aux; // elemento que tomara o lugar de V, quando V rotacionar
    if (*V && (*V)->dir) {  // se existe um elemento para rotacionar e esse elemento possui filho à direita
        aux = (*V)->dir;    // guardando referencia
        (*V)->dir = aux->esq;   // o filho direito de V passa a ser o filho esquerdo de aux
        aux->esq = *V;
        (*V) = aux;
        return 1;
    }
    return 0;
}

int rotacaoDireita(ArvBinPesq* V) {
    ArvBinPesq aux;
    if (*V && (*V)->esq) {
        aux = (*V)->esq;
        (*V)->esq = aux->dir;
        aux->dir = *V;
        (*V) = aux;
        return 1;
    }
    return 0;
}

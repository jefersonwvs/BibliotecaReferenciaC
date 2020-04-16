#include <stdio.h>
#include <stdlib.h>
#include "TADfila.c"

#define TAM 6

typedef Fila GrafoL[TAM];       //Grafo como lista de Adjac�ncias
typedef int GrafoM[TAM][TAM];   //Grafo como matriz de Adjac�ncias

void BFS(GrafoL, int);

int main()
{
    GrafoL Glista;
    GrafoM Gmatriz;
    int i, j, v0;

    //printf("Digite os vertices adjacentes a cada vertice. (-1 para sair): \n");
    for (i = 0; i < TAM; i++) {
        inicializarFila(&Glista[i]);
        /*printf("V(%d): ", i+1);
        scanf("%d", &adj);
        while (adj != -1) {
            enfileirar(&G[i], adj);
            printf("V(%d): ", i+1);
            scanf("%d", &adj);
        }
        printf("\n");*/
    }

    enfileirar(&Glista[0], 1);
    Gmatriz[0][1] = 1;
    enfileirar(&Glista[0], 2);
    Gmatriz[0][2] = 1;

    enfileirar(&Glista[1], 0);
    Gmatriz[1][0] = 1;
    enfileirar(&Glista[1], 2);
    Gmatriz[1][2] = 1;

    enfileirar(&Glista[2], 0);
    Gmatriz[2][0] = 1;
    enfileirar(&Glista[2], 1);
    Gmatriz[2][1] = 1;
    enfileirar(&Glista[2], 3);
    Gmatriz[2][3] = 1;

    enfileirar(&Glista[3], 2);
    Gmatriz[3][2] = 1;
    enfileirar(&Glista[3], 4);
    Gmatriz[3][4] = 1;
    enfileirar(&Glista[3], 5);
    Gmatriz[3][5] = 1;

    enfileirar(&Glista[4], 3);
    Gmatriz[4][3] = 1;
    enfileirar(&Glista[4], 5);
    Gmatriz[4][5] = 1;

    enfileirar(&Glista[5], 3);
    Gmatriz[5][3] = 1;
    enfileirar(&Glista[5], 4);
    Gmatriz[5][4] = 1;

    Gmatriz[2][5] = 0;  //corregindo um bug

    printf("Lista de Adjacencias do grafo G: \n");
    for(i = 0; i < TAM; i++) {
        printf("[%d]---", i);
        imprimeFila(&Glista[i]);
    }

    printf("\nMatriz de Adjacencias do grafo G: \n");
    for(i = 0; i < TAM; i++) {
        for(j = 0; j < TAM; j++) {
            if (Gmatriz[i][j] != 1)
                Gmatriz[i][j] = 0;
            printf("%d ", Gmatriz[i][j]);
        }
        printf("\n");
    }

    printf("\nBFS - Breadth-First Search (Busca em Largura): \n");
    printf("Digite o vertice de origem para a BFS (0 - %d): ", TAM-1);
    scanf("%d", &v0);

    printf("  v: vertice\n");
    printf("  d: distancia da origem\n");
    printf("  p: predecessor\n");
    printf("[(v), d,  p]\n");
    BFS(Glista, v0);

     for(i = 0; i < TAM; i++)
        finalizarFila(&Glista[i]);

    return 0;
}

/*
    DESCRI��O
    Percurso em grafo, que, partindo de um dado v�rtice, acessa os demais.
    Baseado na colora��o:
        - Branco (b): v�rtice ainda n�o visitado
        - Cinza (c): v�rtice sendo visitado, isto �, acessando seus v�rtices adjacentes
        - Preto (p): v�rtice completamente visitado
    PARAM�TROS
        G[]=vetor de v�rtices e suas respectivas listas de adjac�ncias
        v0=v�rtice de origem
*/
void BFS(GrafoL G, int v0) {

    int u;

    char c[TAM];                    // vetor de cores
    int p[TAM];                     // vetor de predecessores
    int d[TAM];                     // vetor de dist�ncias de cada v�rtice em rela��o � origem

    Fila Q;                         // fila para armazenar e ordenar a maneira de explora��o dos v�rtices do grafo

    Fila *uAdj;                     // ponteiro auxiliar para acessar sem complica��es, itera��o a itera��o, a lista de adjac�ncias de cada v�rtice
    celula *v;                      // ponteiro auxiliar para percorrer e acessar cada v�rtice adjacente a um dado v�rtice

    /*Inicializa��o*/
    for(u = 0; u < TAM; u++) {          // Para cada u pertencente ao conjunto de v�rtices
        if (u != v0) {                  // excluindo-se o v�rtice de origem
            c[u] = 'b';                     // pinte-o de branco - ainda n�o visitado
            d[u] = 100;                     // dist�ncia desconhecida
            p[u] = -1;                      // predecessor desconhecido
        }
    }

    c[v0] = 'c';                        //pintura de cinza, pois est� sendo visitado;
    d[v0] = 0;                          //dist�ncia do v�rtice a ele mesmo
    p[v0] = -1;                         //-1 indica que n�o tem predecessor
    inicializarFila(&Q);                //fila que guarda os v�rtices acess�ves a partir de v0. Como se trata de una fila,
    enfileirar(&Q, v0);                 //  o primeiro a entrar ser� o primeiro a ser explorado

    while (!filaVazia(&Q)) {            //enquanto a fila n�o est� vazia
        u = desenfileirar(&Q);          //acesso ao primeiro v�rtice (u) da fila
        uAdj = &G[u];                   //facilitando o acesso, atrav�s de um auxiliar, � lista de adjac�ncias de u
        for(v = uAdj->primeiro; v != NULL; v = v->proxAdj) {    //la�o para acessar todos os v�rtices (v) adjacentes a u
            if (c[v->vertice] == 'b') {                         //condi��o para n�o visitar v�rtices que j� est�o na fila, isto �, aqueles que talvez j� tenham sido acessados atrav�s de outro v�rtice.
                c[v->vertice] = 'c';                            //colora��o que indica que ele ser� enfileirado
                p[v->vertice] = u;                              //registra o antecessor de v
                d[v->vertice] = d[u] + 1;                       //registra a dist�ncia de v0 a v
                enfileirar(&Q, v->vertice);                     //enfileirando v
            }
        }
        c[u] = 'p';                                     //v�rtice visitado. Em outras palavras, todos os seus adjcentes foram colocados na fila, para serem visitados
        printf("[(%d), %d, %2d]\n", u, d[u], p[u]);
    }
    finalizarFila(&Q);                                  //garantia de esvaziamento da fila
}
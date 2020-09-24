#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *arq;

    arq = fopen("meu-arquivo.txt", "w");

    if (arq) {
        fputs("Caraca", arq);
    } else {
        printf("Problema ao ao abrir arquivo!\n");
    }
    fclose(arq);
    return 0;
}

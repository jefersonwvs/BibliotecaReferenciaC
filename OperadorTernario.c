#include <stdio.h>

int main() {

    int x = 5, y = 6;

    printf("Como funciona o operador ternario (?): \n");

    x >= y ? printf("%d >= %d\n", x, y) : printf("%d < %d\n", x, y);

    /* O operador ternário: exp1 ? exp2 : exp3 desempenha a mesma função que a estrutura if-else abaixo*/

    if (x >= y)
        printf("%d >= %d\n", x, y);
    else
        printf("%d < %d\n", x, y);

    return 0;
}

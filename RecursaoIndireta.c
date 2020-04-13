#include <stdio.h>
#include <stdlib.h>

int par(int);
int impar(int);

int main() {

    printf("%d\n", impar(3));
    /*  impar(3)
            par(2)
                impar(1)
                    par(0)

    */

    printf("%d", par(4));
    /*  par(4)
            impar(3)
                par(2)
                    impar(1)
                        par(0)
    */

    return 0;
}

int par(int x) {
    x = abs(x); // para considerar valores negativos
    if (x == 0)
        return 1;   // 0 é par
    return impar(x-1);
}

int impar(int x) {
    x = abs(x);
    if (x == 0)
        return 0;
    return par(x-1);
}

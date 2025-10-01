#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "fila.h"
#include "pilha.h"

int main() {
    char entrada[2000];

    printf("Digite uma expressão: ");
    fgets(entrada, sizeof(entrada), stdin); 
    entrada[strcspn(entrada, "\n")] = 0;   // remove /n do final

    

    return 0;
}
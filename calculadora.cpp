#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "fila.h"
#include "pilha.h"
#include "expressao.h"

int main() {
    // para rodar (windows)
    // g++ calculadora.cpp fila.cpp lista.cpp pilha.cpp expressao.cpp -o calculadora
    // .\calculadora.exe

    char entrada[2000];

    printf("Digite uma expressão: ");
    fgets(entrada, sizeof(entrada), stdin); 
    entrada[strcspn(entrada, "\n")] = 0;   // remove /n do final

    Expressao expressao;
    char semEspacos[2000];

    if (expressao.removeEspacos(entrada, semEspacos)) {
        printf("Sem espaços: %s\n", semEspacos);
    } else {
        printf("Erro: expressão mal fomatada!\n");
    }

    return 0;
}
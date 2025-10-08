#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "fila.h"
#include "pilha.h"
#include "lexer.h"

int main() {
    // para rodar
    // g++ main.cpp fila.cpp ... -o calculadora
    // .\calculadora.exe

    try {
        char entrada[2000];
        char expressao[2000];
        Lexer lexer;

        printf("Digite uma expressão: ");
        fgets(entrada, sizeof(entrada), stdin); 
        entrada[strcspn(entrada, "\n")] = 0;   // remove /n do final

        lexer.removeEspacos(entrada, expressao);
        printf("Sem espaços: %s\n", expressao);
    }
    catch (int e) {
        if (e == 7) {
            printf("Erro: expressão mal fomatada!\n");
            return 1;
        }
    }
    return 0;
}
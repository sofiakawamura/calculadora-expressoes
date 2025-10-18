#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "fila.h"
#include "pilha.h"
#include "lexer.h"
#include "shunting_yard.h"

int main() {
    // para rodar
    // g++ main.cpp fila.cpp ... -o calculadora
    // .\calculadora.exe

    try {
        char entrada[2000];
        char expressao[2000];
        Lexer lexer;
        ShuntingYard sy;

        // ler expressão
        printf("Digite uma expressao: ");
        fgets(entrada, sizeof(entrada), stdin); 
        entrada[strcspn(entrada, "\n")] = 0;   // remove /n do final

        // remover espaços
        lexer.removeEspacos(entrada, expressao);
        printf("Sem espacos: %s\n", expressao);

        // tokenizar
        Token* tokens;
        int tamanho;
        lexer.tokenizacao(expressao, &tokens, &tamanho);

        Fila saida;
        sy.shuntingYard(tokens, tamanho, &saida);

        while (!saida.EstaVazia()) {
            Token* t = (Token*) saida.Desenfileirar();
            printf("%s ", t->valor);
        }
        printf("\n");
    }
    catch (int e) {
        if (e == 2) {
            printf("Erro: token desconhecido!\n");
            return 1;
        }
        if (e == 7) {
            printf("Erro: expressao mal fomatada!\n");
            return 1;
        }
    }
    return 0;
}
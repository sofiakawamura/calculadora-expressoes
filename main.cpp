#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "fila.h"
#include "pilha.h"
#include "lexer.h"
#include "shunting_yard.h"
#include "evaluator.h"

int main() {
    // para rodar
    // g++ main.cpp fila.cpp ... -o calculadora
    // .\calculadora.exe

    try {
        char entrada[2000];
        char expressao[2000];
        Lexer lexer;
        ShuntingYard sy;
        Evaluator evaluator;

        // ler expressão
        printf("Digite uma expressao: ");
        fgets(entrada, sizeof(entrada), stdin); 
        entrada[strcspn(entrada, "\n")] = 0;   // remove /n do final

        // remover espaços
        lexer.removeEspacos(entrada, expressao);

        // tokenizar
        Token* tokens;
        int tamanho;
        lexer.tokenizacao(expressao, &tokens, &tamanho);

        // shunting yard
        Fila saida;
        sy.shuntingYard(tokens, tamanho, &saida);

        // resultado
        char* resultado = evaluator.avaliarPosfixa(&saida);
        printf("Resultado: %s\n", resultado);
    }
    catch (int e) {
        if (e == 1) {
            printf("Erro: parênteses desbalanceados!\n");
            return 1;
        }
        if (e == 2) {
            printf("Erro: token desconhecido!\n");
            return 1;
        }
        if (e == 3) {
            printf("Erro: operador sem operandos suficientes!\n");
            return 1;
        }
        if (e == 4) {
            printf("Erro: tipo incompatível!\n");
            return 1;
        }
        if (e == 5) {
            printf("Erro: divisão por 0!\n");
            return 1;
        }
        if (e == 6) {
            printf("Erro: comparação entre tipos diferentes!\n");
            return 1;
        }
        if (e == 7) {
            printf("Erro: expressao mal fomatada!\n");
            return 1;
        }
    }
    return 0;
}
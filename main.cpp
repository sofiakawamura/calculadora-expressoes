#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "fila.h"
#include "pilha.h"
#include "lexer.h"
#include "shunting_yard.h"
#include "evaluator.h"

int main() {
    Lexer lexer;
    ShuntingYard sy;
    Evaluator evaluator;

    while (true) {
        try {
            // selecionar operação
            int opcao;
            printf("\n\nSelecione uma opcao:\n");
            printf("1. Digitar uma expressao\n");
            printf("2. Sair\n");
            printf("Opcao: ");
            scanf("%d", &opcao);
            getchar();

            if (opcao == 2) {
                printf("\nEncerrando o programa.\n");
                break;
            } else if (opcao != 1) {
                printf("\nOpcao invalida! Tente novamente.\n");
                continue;
            }

            char entrada[2000];
            char expressao[2000];

            // ler expressão
            printf("\nDigite uma expressao: ");
            fgets(entrada, sizeof(entrada), stdin); 
            entrada[strcspn(entrada, "\n")] = 0;   // remove /n do final

            // remover espaços
            lexer.removeEspacos(entrada, expressao);
            printf("Expressao sem espacos: %s", expressao);

            // tokenizar
            Token* tokens;
            int tamanho;
            lexer.tokenizacao(expressao, &tokens, &tamanho);

            // exibir infixa
            printf("\nInfixa: ");
            for (int i = 0; i < tamanho; i++) {
                printf("%s", tokens[i].valor);
            }

            // shunting yard
            Fila saida;
            sy.shuntingYard(tokens, tamanho, &saida);

            // exibir posfixa
            printf("\nPosfixa: ");
            Fila copiaSaida = saida;
            while (!copiaSaida.EstaVazia()) {
                Token* token = (Token*) copiaSaida.Desenfileirar();
                printf("%s", token->valor);
            }

            // resultado
            char* resultado = evaluator.avaliarPosfixa(&saida);
            printf("\n\nResultado: %s\n", resultado);

            // retornar para menu
            printf("Pressione qualquer tecla para voltar ao menu principal...");
            getchar();
        }
        catch (int e) {
            if (e == 1) {
                printf("\n\nErro: parênteses desbalanceados!\n");
            } else if (e == 2) {
                printf("\n\nErro: token desconhecido!\n");
            } else if (e == 3) {
                printf("\n\nErro: operador sem operandos suficientes!\n");
            } else if (e == 4) {
                printf("\n\nErro: tipo incompatível!\n");
            } else if (e == 5) {
                printf("\n\nErro: divisão por 0!\n");
            } else if (e == 6) {
                printf("\n\nErro: comparação entre tipos diferentes!\n");
            } else if (e == 7) {
                printf("\n\nErro: expressao mal formatada!\n");
            } else {
                printf("\n\nErro desconhecido!\n");
            }
            printf("Pressione qualquer tecla para voltar ao menu principal...");
            getchar();
        }
    }
    return 0;
}
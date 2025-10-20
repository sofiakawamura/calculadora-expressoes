#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shunting_yard.h"
#include "token.h"
#include "pilha.h"
#include "fila.h"

// retorna a precedência do operador (classifica por faixas numéricas)
int ShuntingYard::precedencia(Token* t) {
    if (strcmp(t->valor, "!") == 0) return 5;
    if (strcmp(t->valor, "^") == 0) return 4;
    if (strcmp(t->valor, "*") == 0 || strcmp(t->valor, "/") == 0) return 3;
    if (strcmp(t->valor, "+") == 0 || strcmp(t->valor, "-") == 0) return 2;
    if (strcmp(t->valor, ">") == 0 || strcmp(t->valor, "<") == 0 || strcmp(t->valor, ">=") == 0 || strcmp(t->valor, "<=") == 0) return 1;
    if (strcmp(t->valor, "==") == 0 || strcmp(t->valor, "!=") == 0) return 1;
    if (strcmp(t->valor, "&&") == 0) return 0;
    if (strcmp(t->valor, "||") == 0) return -1;
    return -2;
}

bool ShuntingYard::ehOperador(Token* t) {
    return (t->tipo == Token::ARITMETICO ||
            t->tipo == Token::RELACIONAL ||
            t->tipo == Token::LOGICO);
}

bool ShuntingYard::ehUnario(Token* t) {
    return strcmp(t->valor, "!") == 0;
}

bool ShuntingYard::esquerdaAssociativo(Token* t) {
    // ^ e ! são associativos à direita
    if (strcmp(t->valor, "^") == 0 || ehUnario(t))
        return false;
    return true;
}

void ShuntingYard::shuntingYard(Token* entrada, int tamanho, Fila* saida) {
    Pilha operadores;
    Token* atual;

    // percorre todos os tokens
    for (int i = 0; i < tamanho; i++) {
        atual = &entrada[i];

        // numeros e booleanos vão direto para a fila
        if (atual->tipo == Token::NUMERO || atual->tipo == Token::BOOLEANO) {
            saida->Enfileirar(atual);
        }

        else if (ehOperador(atual)) {
            // impede operador duplo isolado
            if ((strcmp(atual->valor, "|") == 0 || strcmp(atual->valor, "&") == 0) &&
                (i + 1 >= tamanho || strcmp(entrada[i + 1].valor, atual->valor) != 0)) {
                throw 2; // operador inválido (desconhecido)
            }

            // verifica as precidências dos operadores
            while (!operadores.EstaVazia()) {
                Token* topo = (Token*) operadores.Topo();

                // abre parênteses é descartado quando é desempilhado
                if (topo->tipo == Token::PARENTESES && strcmp(topo->valor, "(") == 0)
                    break;

                int p1 = precedencia(atual);
                int p2 = precedencia(topo);

                // precedência do operador na pilha é maior -> move para a fila
                if (p2 > p1 || (p2 == p1 && esquerdaAssociativo(atual))) {
                    saida->Enfileirar(operadores.Desempilhar());
                } 
                else {
                    break; // desempilha até a precedência ser menor
                }
            }
            operadores.Empilhar(atual); 
        }

        // empilha parênteses de abertura
        else if (atual->tipo == Token::PARENTESES && strcmp(atual->valor, "(") == 0) {
            operadores.Empilhar(atual);
        }

        // parênteses de fechamento -> desempilha até achar de abertura
        else if (atual->tipo == Token::PARENTESES && strcmp(atual->valor, ")") == 0) {
            bool achouAbre = false;
            while (!operadores.EstaVazia()) {
                Token* topo = (Token*) operadores.Topo();
                if (topo->tipo == Token::PARENTESES && strcmp(topo->valor, "(") == 0) {
                    operadores.Desempilhar(); // descarta "(" e sai do loop
                    achouAbre = true;
                    break;
                } 
                else {
                    saida->Enfileirar(operadores.Desempilhar()); // move o operador da pilha para a fila
                }
            }
            if (!achouAbre)
                throw 1; // parênteses desbalanceados
        }

        else {
            throw 2; // token desconhecido
        }
    }

    // termina de enfileirar operadores
    while (!operadores.EstaVazia()) {
        Token* topo = (Token*) operadores.Desempilhar();
        if (topo->tipo == Token::PARENTESES)
            throw 1; // parênteses desbalanceados
        saida->Enfileirar(topo);
    }
}
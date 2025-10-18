#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shunting_yard.h"
#include "token.h"
#include "pilha.h"
#include "fila.h"

int ShuntingYard::precedencia(Token* t) {
    if (strcmp(t->valor, "!") == 0) return 5;        // unário
    if (strcmp(t->valor, "^") == 0) return 4;
    if (strcmp(t->valor, "*") == 0 || strcmp(t->valor, "/") == 0) return 3;
    if (strcmp(t->valor, "+") == 0 || strcmp(t->valor, "-") == 0) return 2;
    if (strcmp(t->valor, ">") == 0 || strcmp(t->valor, "<") == 0 ||
        strcmp(t->valor, ">=") == 0 || strcmp(t->valor, "<=") == 0) return 1;
    if (strcmp(t->valor, "==") == 0 || strcmp(t->valor, "!=") == 0) return 1;
    if (strcmp(t->valor, "&&") == 0) return 0;
    if (strcmp(t->valor, "||") == 0) return -1;
    return -2; // não é operador
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
    Pilha operadores;  // pilha de operadores
    Token* atual;

    for (int i = 0; i < tamanho; i++) {
        atual = &entrada[i];

        // 1️⃣ — Operando (número ou booleano)
        if (atual->tipo == Token::NUMERO || atual->tipo == Token::BOOLEANO) {
            saida->Enfileirar(atual);
        }

        // 2️⃣ — Operador
        else if (ehOperador(atual)) {
            // validação extra: impede operador duplo isolado (ex: "true | false")
            if ((strcmp(atual->valor, "|") == 0 || strcmp(atual->valor, "&") == 0) &&
                (i + 1 >= tamanho || strcmp(entrada[i + 1].valor, atual->valor) != 0)) {
                throw 2; // token desconhecido
            }

            while (!operadores.EstaVazia()) {
                Token* topo = (Token*) operadores.Topo();

                if (topo->tipo == Token::PARENTESES && strcmp(topo->valor, "(") == 0)
                    break;

                int p1 = precedencia(atual);
                int p2 = precedencia(topo);

                if (p2 > p1 || (p2 == p1 && esquerdaAssociativo(atual))) {
                    saida->Enfileirar(operadores.Desempilhar());
                } else {
                    break;
                }
            }
            operadores.Empilhar(atual);
        }

        // 3️⃣ — Parênteses abrindo
        else if (atual->tipo == Token::PARENTESES && strcmp(atual->valor, "(") == 0) {
            operadores.Empilhar(atual);
        }

        // 4️⃣ — Parênteses fechando
        else if (atual->tipo == Token::PARENTESES && strcmp(atual->valor, ")") == 0) {
            bool achouAbre = false;
            while (!operadores.EstaVazia()) {
                Token* topo = (Token*) operadores.Topo();
                if (topo->tipo == Token::PARENTESES && strcmp(topo->valor, "(") == 0) {
                    operadores.Desempilhar(); // descarta '('
                    achouAbre = true;
                    break;
                } else {
                    saida->Enfileirar(operadores.Desempilhar());
                }
            }
            if (!achouAbre)
                throw 1; // parênteses desbalanceados
        }

        else {
            throw 2; // token desconhecido
        }
    }

    // 5️⃣ — Esvazia a pilha
    while (!operadores.EstaVazia()) {
        Token* topo = (Token*) operadores.Desempilhar();
        if (topo->tipo == Token::PARENTESES)
            throw 1; // parênteses desbalanceados
        saida->Enfileirar(topo);
    }
}
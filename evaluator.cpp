#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "evaluator.h"
#include "pilha.h"
#include "fila.h"
#include "token.h"
#include "exception.h"

// conversão de strings booleanas
bool Evaluator::ehBoolStr(const char* v) {
    return (strcmp(v, "true") == 0 || strcmp(v, "false") == 0);
}

bool Evaluator::strToBool(const char* v) {
    return (strcmp(v, "true") == 0);
}

char* Evaluator::boolToStr(bool v) {
    if (v)
        return strdup("true");
    else
        return strdup("false");
}

// resultado da expressão posfixa
char* Evaluator::avaliarPosfixa(Fila* filaPosfixa) {
    Pilha pilha;
    Token* tk;

    while (!filaPosfixa->EstaVazia()) {
        tk = (Token*) filaPosfixa->Desenfileirar();

        // números e booleanos -> pilha (string)
        if (tk->tipo == Token::NUMERO || tk->tipo == Token::BOOLEANO) {
            pilha.Empilhar(strdup(tk->valor));
        }
    
        // artiméticos
        else if (tk->tipo == Token::ARITMETICO) {
            // últimos operandos da pilha
            char* b = (char*) pilha.Desempilhar();
            char* a = (char*) pilha.Desempilhar();
            if (!a || !b) 
                throw Exception(3, tk->valor);  // operador sem operandos suficientes

            // verificação de tipo
            if (ehBoolStr(a) || ehBoolStr(b))
                throw Exception(4, tk->valor); // tipo incompatível (operadores aritméticos aplicados a booleanos)

            // converte para double
            double opA = atof(a);
            double opB = atof(b);
            double res = 0;

            switch (tk->valor[0]) {
                case '+': 
                    res = opA + opB; 
                    break;
                case '-': 
                    res = opA - opB; 
                    break;
                case '*': 
                    res = opA * opB; 
                    break;
                case '/':
                    if (opB == 0) 
                        throw Exception(5); // divisão por 0
                    res = opA / opB;
                    break;
                case '^': 
                    res = pow(opA, opB); 
                    break;
                default: 
                    throw Exception(2, tk->valor);
            }

            // formata para string com 2 casas decimais e empilha
            char buffer[32];
            sprintf(buffer, "%.2f", res);
            pilha.Empilhar(strdup(buffer));

            free(a);
            free(b);
        }

        // relacionais
        else if (tk->tipo == Token::RELACIONAL) {
            // últimos operandos da pilha
            char* b = (char*) pilha.Desempilhar();
            char* a = (char*) pilha.Desempilhar();
            if (!a || !b) 
                throw Exception(3, tk->valor); // operador sem operandos suficientes

            // verificação de tipo
            bool aIsBool = ehBoolStr(a);
            bool bIsBool = ehBoolStr(b);
            bool r = false;

            // operadores que só aceitam números
            if (strcmp(tk->valor, ">") == 0 || strcmp(tk->valor, "<") == 0 || strcmp(tk->valor, ">=") == 0 || strcmp(tk->valor, "<=") == 0) {
                if (aIsBool || bIsBool)
                    throw Exception(4, tk->valor); // tipo incompatível (operadores relacionais aplicados a booleanos)
                
                // converte para double
                double opA = atof(a);
                double opB = atof(b);

                if (strcmp(tk->valor, ">") == 0) r = opA > opB;
                else if (strcmp(tk->valor, "<") == 0) r = opA < opB;
                else if (strcmp(tk->valor, ">=") == 0) r = opA >= opB;
                else if (strcmp(tk->valor, "<=") == 0) r = opA <= opB;
            } 
            // operadores que permitem números ou booleanos, mas não tipos mistos
            else if (strcmp(tk->valor, "==") == 0 || strcmp(tk->valor, "!=") == 0) {
                 // tipo incompatível (operadores de igualdade aplicados a tipos mistos)
                if (aIsBool != bIsBool)
                    throw Exception(6, tk->valor);
                
                // booleanos
                if (aIsBool && bIsBool) {
                    bool opA = strToBool(a);
                    bool opB = strToBool(b);
                    if (strcmp(tk->valor, "==") == 0) r = (opA == opB);
                    else r = (opA != opB);
                } 
                // números
                else {
                    double opA = atof(a);
                    double opB = atof(b);
                    if (strcmp(tk->valor, "==") == 0) r = (opA == opB);
                    else r = (opA != opB);
                }
            } 
            // token desconhecido
            else {
                throw Exception(2, tk->valor);
            }

            // empilha resultado
            pilha.Empilhar(boolToStr(r));

            free(a);
            free(b);
        }

        // lógicos
        else if (tk->tipo == Token::LOGICO) {
            // operador unário (!)
            if (strcmp(tk->valor, "!") == 0) {
                char* v = (char*) pilha.Desempilhar();
                if (!v) 
                    throw Exception(3, tk->valor); // sem operandos suficientes
                if (!ehBoolStr(v)) 
                    throw Exception(4, tk->valor); // tipo incompatível (negação de número)

                bool res = !strToBool(v);
                pilha.Empilhar(boolToStr(res));
                free(v);
            }
            // operadores binários (&&, ||)
            else {
                // últimos operandos da pilha
                char* b = (char*) pilha.Desempilhar();
                char* a = (char*) pilha.Desempilhar();
                if (!a || !b) 
                    throw Exception(3, tk->valor); // sem operandos suficientes
                if (!ehBoolStr(a) || !ehBoolStr(b)) 
                    throw Exception(4, tk->valor); // tipo incompatível (comparação lógica com números)

                // converte para bool
                bool opA = strToBool(a);
                bool opB = strToBool(b);
                bool res;

                if (strcmp(tk->valor, "&&") == 0) res = opA && opB;
                else if (strcmp(tk->valor, "||") == 0) res = opA || opB;
                else throw Exception(2, tk->valor);

                // empilha resultado
                pilha.Empilhar(boolToStr(res));
                free(a);
                free(b);
            }
        }

        // token desconhecido
        else {
            throw Exception(2, tk->valor);
        }
    }

    // deve sobrar só o resultado final
    char* resultado = (char*) pilha.Desempilhar();

    if (!resultado) 
        throw Exception(7); // sem resultado -> erro de formatação
    if (!pilha.EstaVazia()) 
        throw Exception(7); // sobrou tokens -> erro de formatação

    return resultado;
}
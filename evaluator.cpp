#include "evaluator.h"
#include "pilha.h"
#include "fila.h"
#include "token.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

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

char* Evaluator::avaliarPosfixa(Fila* filaPosfixa) {
    Pilha pilha;
    Token* tk;

    while (!filaPosfixa->EstaVazia()) {
        tk = (Token*) filaPosfixa->Desenfileirar();

        // números e booleanos
        if (tk->tipo == Token::NUMERO || tk->tipo == Token::BOOLEANO) {
            pilha.Empilhar(strdup(tk->valor));
        }
    
        // artiméticos
        else if (tk->tipo == Token::ARITMETICO) {
            char* b = (char*) pilha.Desempilhar();
            char* a = (char*) pilha.Desempilhar();
            if (!a || !b) throw 3; // operador sem operandos suficientes

            double opA = atof(a);
            double opB = atof(b);
            double res = 0;

            switch (tk->valor[0]) {
                case '+': res = opA + opB; break;
                case '-': res = opA - opB; break;
                case '*': res = opA * opB; break;
                case '/':
                    if (opB == 0) throw 5; // divisão por 0
                    res = opA / opB;
                    break;
                case '^': res = pow(opA, opB); break;
                default: throw 2; // token desconhecido
            }

            char buffer[32];
            sprintf(buffer, "%.2f", res);
            pilha.Empilhar(strdup(buffer));

            free(a);
            free(b);
        }

        // relacionais
        else if (tk->tipo == Token::RELACIONAL) {
            char* b = (char*) pilha.Desempilhar();
            char* a = (char*) pilha.Desempilhar();
            if (!a || !b) throw 3;

            double opA = atof(a);
            double opB = atof(b);
            bool r = false;

            if (strcmp(tk->valor, ">") == 0) r = opA > opB;
            else if (strcmp(tk->valor, "<") == 0) r = opA < opB;
            else if (strcmp(tk->valor, ">=") == 0) r = opA >= opB;
            else if (strcmp(tk->valor, "<=") == 0) r = opA <= opB;
            else if (strcmp(tk->valor, "==") == 0) r = (opA == opB);
            else if (strcmp(tk->valor, "!=") == 0) r = (opA != opB);
            else throw 2;

            pilha.Empilhar(boolToStr(r));

            free(a);
            free(b);
        }

        // lógicos
        else if (tk->tipo == Token::LOGICO) {
            // operador unário (!)
            if (strcmp(tk->valor, "!") == 0) {
                char* v = (char*) pilha.Desempilhar();
                if (!v) throw 3;
                if (!ehBoolStr(v)) throw 4; // tipo incompatível

                bool res = !strToBool(v);
                pilha.Empilhar(boolToStr(res));
                free(v);
            }
            // operadores binários (&&, ||)
            else {
                char* b = (char*) pilha.Desempilhar();
                char* a = (char*) pilha.Desempilhar();
                if (!a || !b) throw 3;
                if (!ehBoolStr(a) || !ehBoolStr(b)) throw 4;

                bool opA = strToBool(a);
                bool opB = strToBool(b);
                bool res;

                if (strcmp(tk->valor, "&&") == 0) res = opA && opB;
                else if (strcmp(tk->valor, "||") == 0) res = opA || opB;
                else throw 2;

                pilha.Empilhar(boolToStr(res));
                free(a);
                free(b);
            }
        }

        else {
            throw 2;
        }
    }

    char* resultado = (char*) pilha.Desempilhar();
    if (!resultado) throw 7; // expressão mal-formada
    if (!pilha.EstaVazia()) throw 7; // sobrou item = erro sintático

    return resultado;
}
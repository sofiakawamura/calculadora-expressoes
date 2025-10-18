#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include "pilha.h"

bool Lexer::ehNumero(char caracter) {
    char numeros[11] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '.'};

    for (int i = 0; i<11; i++) {
        if (caracter == numeros[i])
            return true;
    }
    return false;
}

bool Lexer::ehAritmetico(char caracter) {
    char operadores[5] = {'+', '-', '*', '/', '^'};

    for (int i = 0; i<5; i++) {
        if (caracter == operadores[i])
            return true;
    }
    return false;
}

bool Lexer::ehRelacional(char caracter) {
    char operadores[4] = {'>', '<', '=', '!'};

    for (int i = 0; i<4; i++) {
        if (caracter == operadores[i])
            return true;
    }
    return false;
}

bool Lexer::ehLogico(char caracter) {
    char operadores[3] = {'!', '|', '&'};

    for (int i = 0; i<3; i++) {
        if (caracter == operadores[i])
            return true;
    }
    return false;
}

bool Lexer::ehParenteses(char caracter) {
    if (caracter == '(' || caracter == ')')
        return true;
    return false;
}

bool Lexer::ehLetraBool(char caracter) {
    char letras[8] = {'t', 'r', 'u', 'e', 'f', 'a', 'l', 's'};

    for (int i = 0; i<8; i++) {
        if (caracter == letras[i])
            return true;
    }
    return false;
}

void Lexer::removeEspacos(char* entrada, char* saida) {
    int i = 0;
    int j = 0;
    int lendoNumero = 0;
    int lendoBooleano = 0;
    char possivelBool[6] = {0};

    while (entrada[i] != '\0') {
        char atual = entrada[i];

        if (atual == ' ') {
            char anterior = (i > 0) ? entrada[i - 1] : '\0';
            char proximo = entrada[i + 1];

            // espaços entre números, operadores ou booleanos
            if (ehNumero(anterior) && ehNumero(proximo)) {
                throw 7;
            }
            if (
                (anterior == '>' && proximo == '=') ||
                (anterior == '<' && proximo == '=') ||
                (anterior == '=' && proximo == '=') ||
                (anterior == '!' && proximo == '=') ||
                (anterior == '&' && proximo == '&') ||
                (anterior == '|' && proximo == '|')
            ) {
                throw 7;
            }
            if (lendoBooleano > 0) {
                throw 7;
            }
            i++;
            continue;
        }

        if (ehNumero(atual)) {
            lendoNumero = 1;
        } else {
            lendoNumero = 0;
        }
        if (ehLetraBool(atual)) {
            if (lendoBooleano == 0) {
                memset(possivelBool, 0, sizeof(possivelBool));
            }
            if (lendoBooleano < 5) {
                possivelBool[lendoBooleano++] = atual;
                possivelBool[lendoBooleano] = '\0';

                if (strcmp(possivelBool, "true") == 0 || strcmp(possivelBool, "false") == 0) {
                    lendoBooleano = 0;
                }
            } 
            else {
                throw 7;
            }
        } else {
            if (lendoBooleano > 0) {
                throw 7;
            }
        }

        if (!(ehNumero(atual) || ehAritmetico(atual) || ehRelacional(atual) || ehLogico(atual) || ehParenteses(atual) || ehLetraBool(atual))) {
            throw 2;
        }

        saida[j++] = atual;
        i++;
    }

    saida[j] = '\0';
}

void Lexer::tokenizacao(char* expressao, Token** tokens, int* tamanho) {
    int i = 0;
    int capacidade = 70; // capacidade inicial
    *tamanho = 0;
    *tokens = (Token*) malloc(capacidade * sizeof(Token));

    while (expressao[i] != '\0') {
        char c = expressao[i];
        
        // números
        if (ehNumero(c)) {
            int inicio = i;
            while (ehNumero(expressao[i])) 
                i++;
            int tamNumero = i - inicio;

            Token tk;
            tk.tipo = Token::NUMERO;
            tk.valor = (char*) malloc(tamNumero + 1);
            strncpy(tk.valor, &expressao[inicio], tamNumero);
            tk.valor[tamNumero] = '\0';
            
            (*tokens)[(*tamanho)++] = tk;
        }

        // booleanos
        else if (c == 't' || c == 'f') {
            if (strncmp(&expressao[i], "true", 4) == 0) {
                Token tk;
                tk.tipo = Token::BOOLEANO;
                tk.valor = strdup("true");
                (*tokens)[(*tamanho)++] = tk;
                i += 4;
            } 
            else if (strncmp(&expressao[i], "false", 5) == 0) {
                Token tk;
                tk.tipo = Token::BOOLEANO;
                tk.valor = strdup("false");
                (*tokens)[(*tamanho)++] = tk;
                i += 5;
            } 
            else {
                throw 2;
            }
        }

        // lógicos
        else if (ehLogico(c)) {
            Token tk;
            tk.tipo = Token::LOGICO;

            if (c == '&' && expressao[i+1] == '&') {
                tk.valor = strdup("&&");
                i += 2;
            }
            else if (c == '|' && expressao[i+1] == '|') {
                tk.valor = strdup("||");
                i += 2;
            }
            else if (c == '!') {
                tk.valor = strdup("!");
                i++;
            }
            else {
                throw 2;
            }

            (*tokens)[(*tamanho)++] = tk;
        }

        // relacionais
        else if (ehRelacional(c)) {
            Token tk;
            tk.tipo = Token::RELACIONAL;

            // duplos
            if ((c == '>' && expressao[i+1] == '=') || (c == '<' && expressao[i+1] == '=') || (c == '=' && expressao[i+1] == '=') || (c == '!' && expressao[i+1] == '=')) {
                tk.valor = (char*) malloc(3);
                tk.valor[0] = c;
                tk.valor[1] = expressao[i+1];
                tk.valor[2] = '\0';
                i += 2;
            } 
            // simples
            else if (c == '>' || c == '<') {
                tk.valor = (char*) malloc(2);
                tk.valor[0] = c;
                tk.valor[1] = '\0';
                i++;
            } 
            else {
                throw 2;
            }

            (*tokens)[(*tamanho)++] = tk;
        }

        // aritméticos
        else if (ehAritmetico(c)) {
            Token tk;
            tk.tipo = Token::ARITMETICO;
            tk.valor = (char*) malloc(2);
            tk.valor[0] = c;
            tk.valor[1] = '\0';
            (*tokens)[(*tamanho)++] = tk;
            i++;
        }

        // parênteses
        else if (ehParenteses(c)) {
            Token tk;
            tk.tipo = Token::PARENTESES;
            tk.valor = (char*) malloc(2);
            tk.valor[0] = c;
            tk.valor[1] = '\0';
            (*tokens)[(*tamanho)++] = tk;
            i++;
        }

        // caractere inválido
        else {
            throw 2;
        }

        // aumenta o vetor
        if (*tamanho >= capacidade) {
            capacidade *= 2;
            *tokens = (Token*) realloc(*tokens, capacidade * sizeof(Token));
        }
    }
}


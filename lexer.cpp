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
    int lendoOperador = 0;
    int lendoBooleano = 0;
    char possivelBool[6];

    while (entrada[i] != '\0') {
        char atual = entrada[i];

        if (atual == ' ') {
            if (lendoNumero && ehNumero(entrada[i + 1])) {
                throw 7;
            }
            if (lendoOperador && (ehLogico(entrada[i + 1]) || ehAritmetico(entrada[i + 1]))) {
                throw 7;
            }   
            if (lendoBooleano) {
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
        if (ehLogico(atual) || ehAritmetico(atual) || ehRelacional(atual)) {
            lendoOperador = 1;
        } else {
            lendoOperador = 0;
        }
        if (ehLetraBool(atual)) { 
            possivelBool[lendoBooleano++] = atual;
            possivelBool[lendoBooleano] = '\0'; 
            if (strcmp(possivelBool, "true") == 0 || strcmp(possivelBool, "false") == 0) {
                lendoBooleano = 0;
            }
        } else {
            if (lendoBooleano > 0) {
                throw 7;
            }
            lendoBooleano = 0;
        }

        if (!(ehNumero(atual) || ehAritmetico(atual) || ehRelacional(atual) || ehLogico(atual) || ehParenteses(atual) || ehLetraBool(atual))) {
            throw 2;
        }
        
        saida[j] = atual;
        j++;
        i++;
    }

    saida[j] = '\0';
}

void Lexer::tokenizacao(char* expressao, Token** tokens, int* tamanho) {
    
}
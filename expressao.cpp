#include "expressao.h"
#include <stdlib.h>
#include <string.h>

bool Expressao::ehNumero(char caracter) {
    char numeros[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

    for (int i = 0; i<10; i++) {
        if (caracter == numeros[i])
            return true;
    }
    return false;
}

bool Expressao::ehAritmetico(char caracter) {
    char operadores[5] = {'+', '-', '*', '/', '^'};

    for (int i = 0; i<5; i++) {
        if (caracter == operadores[i])
            return true;
    }
    return false;
}

bool Expressao::ehLogico(char caracter) {
    // fazer
    char numeros[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

    for (int i = 0; i<10; i++) {
        if (caracter == numeros[i])
            return true;
    }
    return false;
}

int Expressao::removeEspacos(char* entrada, char* saida) {
    int i = 0; 
    int j = 0; 
    int lendoNumero = 0; 

    while (entrada[i] != '\0') {
        char atual = entrada[i];

        if (atual == ' ') {
            if (lendoNumero && ehNumero(entrada[i + 1])) {
                return 0;
            }
            i++;
            continue;
        }

        if (ehNumero(atual)) {
            lendoNumero = 1;
        } else {
            lendoNumero = 0;
        }
        
        saida[j] = atual;
        j++;
        i++;
    }

    saida[j] = '\0';
    return 1;
}
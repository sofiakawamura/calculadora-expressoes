#include "expressao.h"

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

char* Expressao::removeEspacos(char* entrada) {
    char saida[2000];
    for (int i = 0; i < 2000; i++) {

    }
}
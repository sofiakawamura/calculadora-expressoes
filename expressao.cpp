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
    char operadores[6] = {'>', '<', '=', '!', '|', '&'};

    for (int i = 0; i<6; i++) {
        if (caracter == operadores[i])
            return true;
    }
    return false;
}

bool Expressao::ehExpressaoValida(char* expressao) {
    char* expressaoSemEspacos;

    int resultado = removeEspacos(expressao, expressaoSemEspacos);
    if (resultado == 0)
        return false;

    // se o primeiro caracter da expressão não for número
    if (!ehNumero(expressaoSemEspacos[0]))
        return false;

    int i = 1;
    while  (expressaoSemEspacos[i+1] != '\0') {
        char anterior = expressaoSemEspacos[i-1];
        char atual = expressaoSemEspacos[1];
        char proximo = expressaoSemEspacos[i+1];

        if (ehLogico(atual)) {
            if (ehLogico(anterior) && ehLogico(proximo))
                return false;
            if (ehAritmetico(anterior) || ehAritmetico(proximo))
                return false;
            
            // verificação de possíveis sequencias inválidas
            if (ehLogico(anterior)) {
                if (atual == '>' || atual == '<' || atual == '!')
                    return false;

                if (atual == '=')
                    if (anterior == '|' || anterior == '&')
                        return false;

                if (anterior == '=' && atual != '=')
                    return false;
                if (atual == '&' && anterior != '&')
                    return false;
                if (atual == '|' && anterior != '|')
                    return false;
            }

            if (ehLogico(proximo)) {
                if (proximo == '>' || proximo == '<' || proximo == '!')
                    return false;

                if (proximo == '=')
                    if (atual == '|' || atual == '&')
                        return false;

                if (atual == '=' && proximo != '=')
                    return false;
                if (atual == '&' && proximo != '&')
                    return false;
                if (atual == '|' && proximo != '|')
                    return false;
            }
        }

        if (ehAritmetico(atual))
            if (!ehNumero(anterior) || !ehNumero(proximo))
                return false;

        i += 1;
    }

    // se o último caracter da expressão não for um número
    if (!ehNumero(expressaoSemEspacos[i]))
        return false;

    return true;
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
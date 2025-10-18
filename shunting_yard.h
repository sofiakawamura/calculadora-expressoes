#ifndef SHUNTING_YARD
#define SHUNTING_YARD
#include "token.h"
#include "fila.h"

class ShuntingYard
{
public:
    void shuntingYard(Token* entrada, int tamanho, Fila* saida);
private:
    int precedencia(Token* t);
    bool ehOperador(Token* t);
    bool ehUnario(Token* t);
    bool esquerdaAssociativo(Token* t);
};
#endif
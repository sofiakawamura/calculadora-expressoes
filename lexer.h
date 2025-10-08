#ifndef LEXER
#define LEXER
#include "token.h"

class Lexer
{
public:
    void removeEspacos(char* entrada, char* saida);
    void tokenizacao(char* expressao, Token** tokens, int* tamanho);
private:
    bool ehNumero(char caracter);
    bool ehRelacional(char caracter);
    bool ehAritmetico(char caracter);
    bool ehLogico(char caracter);
    bool ehParenteses(char caracter);
    bool ehLetraBool(char caracter);
};
#endif
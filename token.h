#ifndef TOKEN
#define TOKEN

struct Token {
    enum Tipo { NUMERO, BOOLEANO, LOGICO, RELACIONAL, ARITMETICO, PARENTESES } tipo;
    char* valor;
};

#endif
#ifndef TOKEN
#define TOKEN

// struct para poder armazenar diferentes tipos de tokens nas estruturas
struct Token {
    enum Tipo { NUMERO, BOOLEANO, LOGICO, RELACIONAL, ARITMETICO, PARENTESES } tipo;
    char* valor;
};

#endif
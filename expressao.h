#ifndef EXPRESSAO
#define EXPRESSAO

class Expressao
{
public:
    char* removeEspacos(char* entrada);
private:
    bool ehNumero(char caracter);
    bool ehAritmetico(char caracter);
    bool ehLogico(char caracter);
};
#endif
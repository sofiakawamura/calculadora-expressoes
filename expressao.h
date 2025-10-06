#ifndef EXPRESSAO
#define EXPRESSAO

class Expressao
{
public:
    int removeEspacos(char* entrada, char* saida);
    bool ehExpressaoValida(char* expressao);
private:
    bool ehNumero(char caracter);
    bool ehAritmetico(char caracter);
    bool ehLogico(char caracter);
};
#endif
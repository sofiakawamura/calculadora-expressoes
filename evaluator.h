#ifndef EVALUATOR
#define EVALUATOR
#include "fila.h"

class Evaluator
{
public:
    char* avaliarPosfixa(Fila* filaPosfixa);
private:
    bool ehBoolStr(const char* v);
    char* boolToStr(bool v);
    bool strToBool(const char* v);
};
#endif
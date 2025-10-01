#ifndef PILHA
#define PILHA
#include "lista.h"

class Pilha : private Lista
{
public:
    Pilha();
    Pilha(const Pilha &);
    ~Pilha();
    Pilha &operator=(const Pilha &);
    void Empilhar(void*);
    void* Desempilhar();
    void* Topo();
    int EstaVazia();
    char *NaFormaDeString() const;
};
#endif
#ifndef FILA
#define FILA
#include <lista.h>

class Fila : private Lista
{
public:
    Fila();
    Fila(const Fila &);
    ~Fila();
    Fila &operator=(const Fila &);
    void Enfileirar(void*);
    void* Desenfileirar();
    void* Primeiro();
    void* Ultimo();
    int EstaVazia();
    char *NaFormaDeString() const;
};
#endif
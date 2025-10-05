#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "lista.h"

char Lista::Erro = 0;
void Lista::DescarteTudo()
{
    pNo P = this->Inicio;
    while (P != NULL) {
        pNo temp = P;
        P = P->Prox;
        delete temp;
    }
    this->Inicio = NULL;
}
char Lista::DeuErro()
{
    return Lista::Erro;
}
char Lista::eValida() const
{
    return this->Valida;
}
Lista::Lista() : Inicio(NULL), Valida(1)
{
}
Lista::Lista(const Lista &L) : Inicio(NULL), Valida(1)
{
    *this = L;
}
Lista::~Lista()
{
    this->DescarteTudo();
}
Lista &Lista::operator=(const Lista &L)
{
    this->DescarteTudo();
    this->Valida = 1;
    Lista::Erro = 0;
    pNo PT, PL;

    for (PL = L.Inicio; PL != NULL; PL = PL->Prox) if (this->Inicio == NULL)
    {
        if ((this->Inicio = new sNo) == NULL)
        {
            this->Valida = 0;
            Lista::Erro = 1;
            break;
        }
        this->Inicio->Info = PL->Info;
        this->Inicio->Prox = NULL;
        PT = this->Inicio;
    }
    else
    {
        if ((PT->Prox = new sNo) == NULL)
        {
            this->Valida = 0;
            Lista::Erro = 1;
            break;
        }
        PT = PT->Prox;
        PT->Info = PL->Info;
        PT->Prox = NULL;
    }
    return *this;
}
void Lista::Incorpore(void* I)
{
    Lista::Erro = 0;
    if (!this->Valida)
    {
        Lista::Erro = 1;
        return;
    }
    if (this->Inicio == NULL)
    {
        if ((this->Inicio = new sNo) == NULL)
        {
            Lista::Erro = 1;
            return;
        }
        this->Inicio->Info = I;
        this->Inicio->Prox = NULL;
        return;
    }
    if (I < this->Inicio->Info)
    {
        pNo N;
        if ((N = new sNo) == NULL)
        {
            Lista::Erro = 1;
            return;
        }
        N->Info = I;
        N->Prox = this->Inicio;
        this->Inicio = N;
        return;
    }
    pNo A, P;
    for (A = NULL, P = this->Inicio;; A = P, P = P->Prox)
    {
        if (P == NULL)
            break;
        if (I < P->Info)
            break;
    }
    pNo N;
    if ((N = new sNo) == NULL)
    {
        Lista::Erro = 1;
        return;
    }
    N->Info = I;
    N->Prox = P;
    A->Prox = N;
}
int Lista::Contem(void* I) const
{
    Lista::Erro = 0;
    if (!this->Valida)
    {
        Lista::Erro = 1;
        return -1;
    }
    for (pNo P = Inicio; P != NULL; P = P->Prox) {
        if (P->Info == I) {
            return 1;
        }
    }
    return 0;
}
void Lista::Descarte(void* I)
{
    Lista::Erro = 0;
    if (!this->Valida || this->Inicio == NULL)
    {
        Lista::Erro = 1;
        return;
    }
    pNo A, P;
    int Achou = 0, Prim = 1;

    for (A = NULL, P = this->Inicio;; A = P, P = P->Prox, Prim = 0)
    {
        if (P == NULL)
            break;
        if (P->Info == I)
        {
            Achou = 1;
            break;
        }
    }
    if (!Achou)
    {
        Lista::Erro = 1;
        return;
    }
    if (Prim)
        Inicio = P->Prox;
    else
        A->Prox = P->Prox;
    delete P;
}
char *Lista::NaFormaDeString() const
{
    Lista::Erro = 0;
    if (!this->Valida)
    {
        Lista::Erro = 1;
        return NULL;
    }
    static char S[16], R[1025];
    strcpy(R, "");
    for (pNo P = this->Inicio; P != NULL; P = P->Prox)
    {
        sprintf(S, "%d", P->Info);
        strcat(R, S);
        strcat(R, P->Prox == NULL ? "" : ", ");
    }
    return R;
}

void Lista::IncorporeNoInicio(void* I)
{
    pNo N;
    if ((N = new sNo) == NULL)
    {
        Lista::Erro = 1;
        return;
    }
    N->Info = I;
    N->Prox = Inicio;
    Inicio = N;
}
void* Lista::DescarteDoInicio()
{
    if (Inicio == NULL)
    {
        Lista::Erro = 1;
        return NULL;
    }
    void* R = Inicio->Info;
    pNo P = Inicio;
    Inicio = Inicio->Prox;
    delete P;
    return R;
}
void Lista::IncorporeNoFinal(void* I)
{
    if (Inicio == NULL)
    {

        if ((Inicio = new sNo) == NULL)
        {
            Lista::Erro = 1;
            return;
        }
        Inicio->Info = I;
        Inicio->Prox = NULL;
    }
    else
    {
        pNo A, P, N;
        for (A = NULL, P = Inicio; P != NULL; A = P, P = P->Prox)
            ;
        if ((N = new sNo) == NULL)
        {
            Lista::Erro = 1;
            return;
        }
        N->Info = I;
        N->Prox = NULL;
        A->Prox = N;
    }
}
void* Lista::DescarteDoFinal()
{
    if (Inicio == NULL)
    {
        Lista::Erro = 1;
        return NULL;
    }
    void* R;
    if (Inicio->Prox == NULL)
    {
        R = Inicio->Info;
        delete Inicio;
        Inicio = NULL;
    }
    else
    {
        pNo A, P, D;
        for (A = Inicio, P = Inicio->Prox, D = P->Prox;
             D != NULL;
             A = P, P = D, D = D->Prox)
            ;
        R = P->Info;
        A->Prox = NULL;
        delete P;
    }
    return R;
}
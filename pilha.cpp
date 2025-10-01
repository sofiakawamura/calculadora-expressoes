#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "pilha.h"

Pilha::Pilha() : Lista() {
}

Pilha::Pilha(const Pilha &outra) : Lista(outra) {
}

Pilha::~Pilha() {
}

Pilha &Pilha::operator=(const Pilha &outra) {
    if (this != &outra) {
        Lista::operator=(outra);
    }
    return *this;
}

void Pilha::Empilhar(void* valor) {
    IncorporeNoInicio(valor);
}

void* Pilha::Desempilhar() {
    return DescarteDoInicio();
}

void* Pilha::Topo() {
    if (Inicio != nullptr) {
        return Inicio->Info;
    }
    return nullptr; 
}

int Pilha::EstaVazia() {
    return (Inicio == nullptr);
}

char *Pilha::NaFormaDeString() const {
    return Lista::NaFormaDeString();
}

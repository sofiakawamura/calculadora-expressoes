#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "fila.h"

Fila::Fila() : Lista() {
}

Fila::Fila(const Fila &outra) : Lista(outra) {
}

Fila::~Fila() {
}

Fila &Fila::operator=(const Fila &outra) {
    if (this != &outra) {
        Lista::operator=(outra);
    }
    return *this;
}

void Fila::Enfileirar(void* valor) {
    IncorporeNoFinal(valor);
}

void* Fila::Desenfileirar() {
    return DescarteDoInicio();
}

void* Fila::Primeiro() {
    if (Inicio != nullptr) {
        return Inicio->Info;
    }
    return nullptr;
}

void* Fila::Ultimo() {
    pNo temp = Inicio;
    while (temp && temp->Prox != nullptr) {
        temp = temp->Prox;
    }
    if (temp != nullptr) {
        return temp->Info; 
    }
    return nullptr;
}

int Fila::EstaVazia() {
    return (Inicio == nullptr);
}

char* Fila::NaFormaDeString() const {
    return Lista::NaFormaDeString();
}

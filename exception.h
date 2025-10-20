#include <stdlib.h>
#include <string.h>

// struct exceção para erros de avaliação
struct Exception {
    int code; // código de erro
    char* token; // token associado (se houver)

    Exception(int c, const char* t = nullptr) {
        code = c;

        // se o token for fornecido, aloca e copia a string
        if (t) {
            token = strdup(t);
        } else {
            token = nullptr;
        }
    }

    ~Exception() {
        // libera a memória alocada para o token, se existir
        if (token) {
            free(token);
        }
    }
};

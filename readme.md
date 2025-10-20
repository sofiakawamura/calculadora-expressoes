# Calculadora de Expressões

Este projeto é uma calculadora de expressões aritméticas, relacionais e lógicas, implementada em C++ utilizando apenas C-strings (`char*`) para manipulação de textos. O sistema suporta entrada de expressões infixas, conversão para notação pós-fixa e avaliação do resultado, incluindo tratamento de erros.

## Arquitetura do Código

O projeto é modularizado em diversos arquivos, cada um responsável por uma parte da lógica:

- **main.cpp**: Interface principal do usuário, menu, leitura de entrada, exibição de resultados e tratamento de exceções.
- **lexer.h/cpp**: Tokenização da expressão, remoção de espaços e validação dos tokens.
- **shunting_yard.h/cpp**: Implementação do algoritmo de Shunting Yard para converter expressões infixas em pós-fixas.
- **evaluator.h/cpp**: Avaliação da expressão pós-fixa, incluindo operações aritméticas, relacionais e lógicas.
- **pilha.h/cpp**: Implementação de uma pilha genérica para uso interno.
- **fila.h/cpp**: Implementação de uma fila genérica para uso interno.
- **token.h**: Definição da estrutura de token e tipos de token.
- **exception.h**: Estrutura de exceção personalizada para propagação de erros com código e token (usando apenas `char*`).

## Compilação

O projeto pode ser compilado com qualquer compilador C++ moderno (g++, clang++, MSVC). Exemplo usando g++:

```sh
# No diretório do projeto

g++ -o calculadora main.cpp lexer.cpp shunting_yard.cpp evaluator.cpp pilha.cpp fila.cpp
```

Certifique-se de que todos os arquivos .cpp e .h estejam no mesmo diretório.

## Execução

Após compilar, execute o programa:

```sh
./calculadora
```

O menu principal será exibido:

```
Selecione uma opcao:
1. Digitar uma expressao
2. Sair
Opcao:
```

### Opções
- **1. Digitar uma expressao**: Permite inserir uma expressão para ser avaliada.  
- **2. Sair**: Encerra o programa.

Para usar a calculadora, escolha a opção 1, digite a expressão desejada (ex: `3+4*2/(1-5)^2^3`) e pressione Enter. O programa mostrará a expressão sem espaços, a forma infixa, a forma pós-fixa e o resultado.

## Tratamento de Casos Limite

O sistema trata diversos casos de erro, lançando exceções personalizadas:

- Parênteses desbalanceados
- Token desconhecido (exibe o token inválido)
- Operador sem operandos suficientes (exibe o operador)
- Tipo incompatível para operação (exibe operação)
- Divisão por zero
- Comparação entre tipos diferentes (exibe a operação)
- Expressão mal formatada

Ao ocorrer um erro, uma mensagem descritiva é exibida e o usuário pode retornar ao menu principal.

## Decisões de Projeto

- **Uso de C-strings**: Por restrição do projeto, todas as manipulações de texto são feitas com `char*` e funções da string.h.
- **Exceções personalizadas**: Implementação de uma struct `Exception` para transportar código de erro e token inválido, facilitando o diagnóstico.
- **Estrutura personalizada para Token**: Implementação de uma struct `Token` para noermalizar e tratar diferentes tipos de operadores e operandos.
- **Estruturas genéricas**: Pilha e fila implementadas de forma genérica para manipular ponteiros void*.
- **Separação de responsabilidades**: Cada módulo tem uma responsabilidade clara (tokenização, parsing, avaliação, etc).
- **Tratamento de booleanos**: O sistema suporta a entrada de booleanos por meio de texto (`true` e `false`). Na avaliação, os booleanos não podem participar de operações aritméticas e relacionais (apenas de comparações com `==` ou `!=`).

## Limitações

- **Sem suporte a variáveis**: Apenas números e booleanos literais são aceitos.
- **Sem funções matemáticas**: Não há suporte a funções como `sin`, `cos`, etc.
- **Sem precedência customizável**: A precedência dos operadores é fixa conforme implementado no Shunting Yard.
- **Tamanho fixo de entrada**: O tamanho máximo da expressão é limitado pelo buffer (2000 caracteres).
- **Apenas C-strings**: Não utiliza recursos avançados de C++ como std::string, por restrição do projeto.

## Exemplos de Expressões Suportadas

- `3+4*2/(1-5)^2^3`
- `10 > 5 && 2 < 3`
- `!(true || false)`
- `4 / 0` (gera erro de divisão por zero)
- `3 + * 4` (gera erro de expressão mal formatada)

## Observações

- O código é facilmente extensível para suportar mais operadores ou funções, bastando alterar os módulos de tokenização, parsing e avaliação.
- O tratamento de erros é robusto e informa ao usuário o motivo e o local do erro sempre que possível.

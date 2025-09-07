#ifndef PILHA_H
#define PILHA_H

#include "fila.h" //Inclui para reutilizar a struct Chamado

// Nó da lista encadeada que representa a pilha.
typedef struct PilhaNode {
    Chamado *chamado;
    struct PilhaNode *proximo;
} PilhaNode;

// Estrutura principal da Pilha, com ponteiro para o topo.
typedef struct {
    PilhaNode *topo;
    int total_chamados;
} Pilha;

// Funções de manipulação da pilha.
Pilha* criar_pilha();
void empilhar(Pilha *pilha, Chamado *chamado);
Chamado* desempilhar(Pilha *pilha); // Não é usado no menu, mas é uma operação padrão.
void listar_chamados_pilha(const Pilha *pilha);
Chamado* buscar_na_pilha_recursivo(PilhaNode *node, int id);
void liberar_pilha(Pilha *pilha);

#endif // PILHA_H
#ifndef FILA_H
#define FILA_H

#include <stdio.h>

// Enum para o status do chamado, para maior clareza e segurança de tipo.
typedef enum {
    ABERTO = 1,
    EM_ANDAMENTO,
    FECHADO
} StatusChamado;

// Estrutura para armazenar os dados de um chamado.
typedef struct {
    int id;
    char titulo[101];
    int prioridade; // 1 (mais alta) a 5 (mais baixa)
    StatusChamado status;
} Chamado;

// Nó da lista encadeada que representa a fila.
typedef struct FilaNode {
    Chamado *chamado;
    struct FilaNode *proximo;
} FilaNode;

// Estrutura principal da Fila, com ponteiros para o início e fim.
typedef struct {
    FilaNode *inicio;
    FilaNode *fim;
    int total_chamados;
} Fila;

// Funções de manipulação da fila.
Fila* criar_fila();
void enfileirar(Fila *fila, Chamado *chamado);
Chamado* desenfileirar_prioridade(Fila *fila);
void listar_chamados_fila(const Fila *fila, StatusChamado filtro);
Chamado* buscar_na_fila_recursivo(FilaNode *node, int id);
void liberar_fila(Fila *fila);
const char* status_para_string(StatusChamado status);

#endif // FILA_H
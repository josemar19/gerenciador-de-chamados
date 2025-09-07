#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "fila.h"
#include "log.h"

// Converte o enum StatusChamado para uma string legível.
const char* status_para_string(StatusChamado status) {
    switch (status) {
        case ABERTO: return "Aberto";
        case EM_ANDAMENTO: return "Em Andamento";
        case FECHADO: return "Fechado";
        default: return "Desconhecido";
    }
}

Fila* criar_fila() {
    Fila *fila = (Fila*) malloc(sizeof(Fila));
    // Assert para garantir que a alocação de um componente crítico funcionou.
    assert(fila != NULL);

    fila->inicio = NULL;
    fila->fim = NULL;
    fila->total_chamados = 0;
    registrar_log("Fila de chamados criada com sucesso.");
    return fila;
}

void enfileirar(Fila *fila, Chamado *chamado) {
    assert(fila != NULL && chamado != NULL);

    FilaNode *novo_node = (FilaNode*) malloc(sizeof(FilaNode));
    if (novo_node == NULL) {
        registrar_log("Erro Crítico: Falha na alocação de memória para novo nó da fila.");
        return;
    }
    
    novo_node->chamado = chamado;
    novo_node->proximo = NULL;

    if (fila->fim == NULL) { // Fila vazia
        fila->inicio = novo_node;
        fila->fim = novo_node;
    } else {
        fila->fim->proximo = novo_node;
        fila->fim = novo_node;
    }
    fila->total_chamados++;
    
    char log_msg[150];
    sprintf(log_msg, "Chamado ID %d ('%s') inserido na fila.", chamado->id, chamado->titulo);
    registrar_log(log_msg);
}

Chamado* desenfileirar_prioridade(Fila *fila) {
    assert(fila != NULL);
    if (fila->inicio == NULL) {
        registrar_log("Tentativa de remover de uma fila vazia.");
        return NULL;
    }

    FilaNode *atual = fila->inicio;
    FilaNode *anterior = NULL;
    FilaNode *node_maior_prioridade = fila->inicio;
    FilaNode *anterior_maior_prioridade = NULL;

    // Encontra o nó com a maior prioridade (menor número)
    int maior_prioridade = fila->inicio->chamado->prioridade;
    while (atual != NULL) {
        if (atual->chamado->prioridade < maior_prioridade) {
            maior_prioridade = atual->chamado->prioridade;
            node_maior_prioridade = atual;
            anterior_maior_prioridade = anterior;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    // Remove o nó da lista
    if (node_maior_prioridade == fila->inicio) {
        fila->inicio = node_maior_prioridade->proximo;
        if (fila->inicio == NULL) { // Era o único elemento
            fila->fim = NULL;
        }
    } else {
        anterior_maior_prioridade->proximo = node_maior_prioridade->proximo;
        if (node_maior_prioridade == fila->fim) {
            fila->fim = anterior_maior_prioridade;
        }
    }

    Chamado* chamado_removido = node_maior_prioridade->chamado;
    free(node_maior_prioridade);
    fila->total_chamados--;

    char log_msg[150];
    sprintf(log_msg, "Chamado ID %d removido da fila para atendimento (Prioridade: %d).", chamado_removido->id, chamado_removido->prioridade);
    registrar_log(log_msg);
    
    return chamado_removido;
}

void listar_chamados_fila(const Fila *fila, StatusChamado filtro) {
    assert(fila != NULL);
    FilaNode *atual = fila->inicio;
    int count = 0;

    printf("\n--- Chamados na Fila de Atendimento ---\n");
    if (atual == NULL) {
        printf("Fila de atendimento vazia.\n");
        return;
    }

    while (atual != NULL) {
        // Se filtro for 0, lista todos. Senão, lista apenas com status correspondente.
        if (filtro == 0 || atual->chamado->status == filtro) {
            printf("ID: %d | Título: %s | Prioridade: %d | Status: %s\n",
                   atual->chamado->id,
                   atual->chamado->titulo,
                   atual->chamado->prioridade,
                   status_para_string(atual->chamado->status));
            count++;
        }
        atual = atual->proximo;
    }
    
    if (count == 0) {
        printf("Nenhum chamado encontrado com o filtro especificado.\n");
    }
    printf("---------------------------------------\n");
}


Chamado* buscar_na_fila_recursivo(FilaNode *node, int id) {
    // Caso base 1: Fim da lista, não encontrou.
    if (node == NULL) {
        return NULL;
    }
    // Caso base 2: Encontrou o chamado.
    if (node->chamado->id == id) {
        return node->chamado;
    }
    // Passo recursivo: Procura no resto da lista.
    return buscar_na_fila_recursivo(node->proximo, id);
}

void liberar_fila(Fila *fila) {
    assert(fila != NULL);
    FilaNode *atual = fila->inicio;
    while (atual != NULL) {
        FilaNode *temp = atual;
        atual = atual->proximo;
        free(temp->chamado); // Libera o chamado
        free(temp);          // Libera o nó da fila
    }
    free(fila); // Libera a estrutura da fila
    registrar_log("Memória da fila de chamados liberada.");
}
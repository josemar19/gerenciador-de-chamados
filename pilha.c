#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pilha.h"
#include "log.h"

Pilha* criar_pilha() {
    Pilha *pilha = (Pilha*) malloc(sizeof(Pilha));
    assert(pilha != NULL);

    pilha->topo = NULL;
    pilha->total_chamados = 0;
    registrar_log("Pilha de chamados finalizados criada com sucesso.");
    return pilha;
}

void empilhar(Pilha *pilha, Chamado *chamado) {
    assert(pilha != NULL && chamado != NULL);

    PilhaNode *novo_node = (PilhaNode*) malloc(sizeof(PilhaNode));
    if (novo_node == NULL) {
        registrar_log("Erro Critico: Falha na alocacao de memoria para novo no da pilha.");
        return;
    }

    novo_node->chamado = chamado;
    novo_node->proximo = pilha->topo;
    pilha->topo = novo_node;
    pilha->total_chamados++;

    //Aumentado o tamanho do buffer de 150 para 256
    char log_msg[256];
    sprintf(log_msg, "Chamado ID %d ('%s') movido para a pilha de finalizados.", chamado->id, chamado->titulo);
    registrar_log(log_msg);
}

Chamado* desempilhar(Pilha *pilha) {
    assert(pilha != NULL);
    if (pilha->topo == NULL) {
        return NULL;
    }

    PilhaNode *node_removido = pilha->topo;
    Chamado *chamado_removido = node_removido->chamado;
    pilha->topo = node_removido->proximo;
    
    free(node_removido);
    pilha->total_chamados--;
    
    return chamado_removido;
}


void listar_chamados_pilha(const Pilha *pilha) {
    assert(pilha != NULL);
    PilhaNode *atual = pilha->topo;
    
    printf("\n--- Chamados Finalizados (Pilha) ---\n");
    if (atual == NULL) {
        printf("Nenhum chamado finalizado.\n");
        return;
    }
    
    while (atual != NULL) {
        printf("ID: %d | Titulo: %s | Prioridade: %d | Status: %s\n",
               atual->chamado->id,
               atual->chamado->titulo,
               atual->chamado->prioridade,
               status_para_string(atual->chamado->status));
        atual = atual->proximo;
    }
    printf("-------------------------------------\n");
}

Chamado* buscar_na_pilha_recursivo(PilhaNode *node, int id) {
    // Caso base 1: Fim da lista.
    if (node == NULL) {
        return NULL;
    }
    // Caso base 2: Encontrou.
    if (node->chamado->id == id) {
        return node->chamado;
    }
    // Passo recursivo.
    return buscar_na_pilha_recursivo(node->proximo, id);
}

void liberar_pilha(Pilha *pilha) {
    assert(pilha != NULL);
    PilhaNode *atual = pilha->topo;
    while (atual != NULL) {
        PilhaNode *temp = atual;
        atual = atual->proximo;
        free(temp->chamado); // Libera o chamado
        free(temp);          // Libera o no da pilha
    }
    free(pilha); // Libera a estrutura da pilha
    registrar_log("Memoria da pilha de chamados liberada.");
}
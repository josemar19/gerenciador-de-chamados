#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "log.h" 
#include "fila.h" 
#include "pilha.h"

void exibir_menu() {
    printf("\n--- Sistema de Gerenciamento de Chamados ---\n");
    printf("1. Cadastrar Chamado\n");
    printf("2. Listar Chamados\n");
    printf("3. Executar Atendimento\n");
    printf("4. Buscar Chamado por ID\n");
    printf("5. Exibir Estatísticas\n");
    printf("6. Finalizar Programa\n");
    printf("Escolha uma opcao: ");
}

void limpar_buffer_teclado() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrar_novo_chamado(Fila *fila, int *proximo_id) {
    Chamado *novo_chamado = (Chamado*) malloc(sizeof(Chamado));
    if (novo_chamado == NULL) {
        registrar_log("Erro de alocação ao tentar criar um novo chamado.");
        printf("Erro: Falha ao alocar memória para o chamado!\n");
        return;
    }

    novo_chamado->id = (*proximo_id)++;
    
    printf("Digite o titulo do chamado: ");
    fgets(novo_chamado->titulo, 100, stdin);
    novo_chamado->titulo[strcspn(novo_chamado->titulo, "\n")] = 0; // Remove a nova linha

    // --- Validação da Prioridade ---
    int prioridade_valida = 0;
    do {
        printf("Digite a prioridade (1-5, onde 1 é a mais alta): ");
        char buffer_entrada[16];
        if (fgets(buffer_entrada, sizeof(buffer_entrada), stdin) != NULL) {
            char *endptr;
            long valor_lido = strtol(buffer_entrada, &endptr, 10);

            if (endptr != buffer_entrada && (*endptr == '\n' || *endptr == '\0') && valor_lido >= 1 && valor_lido <= 5) {
                novo_chamado->prioridade = (int)valor_lido;
                prioridade_valida = 1;
            } else {
                printf("Prioridade invalida! Por favor, insira um numero entre 1 e 5.\n");
            }
        }
    } while (!prioridade_valida);

    // --- Validação do Status ---
    int status_valido = 0;
    do {
        printf("Digite o status (1-Aberto, 2-Em Andamento): ");
        char buffer_entrada[16];
        if (fgets(buffer_entrada, sizeof(buffer_entrada), stdin) != NULL) {
            char *endptr;
            long valor_lido = strtol(buffer_entrada, &endptr, 10);
            
            if (endptr != buffer_entrada && (*endptr == '\n' || *endptr == '\0') && (valor_lido == 1 || valor_lido == 2)) {
                novo_chamado->status = (valor_lido == 2) ? EM_ANDAMENTO : ABERTO;
                status_valido = 1;
            } else {
                printf("Status invalido! Por favor, insira 1 para Aberto ou 2 para Em Andamento.\n");
            }
        }
    } while (!status_valido);
    
    enfileirar(fila, novo_chamado);
    printf("Chamado ID %d cadastrado com sucesso!\n\n", novo_chamado->id);
}

void executar_atendimento_chamado(Fila *fila, Pilha *pilha) {
    if (fila->inicio == NULL) {
        printf("Nao ha chamados na fila para atender.\n");
        registrar_log("Tentativa de atendimento com fila vazia.");
        return;
    }

    Chamado* chamado_atendido = desenfileirar_prioridade(fila);
    printf("Atendendo chamado ID %d (Prioridade %d): '%s'\n", chamado_atendido->id, chamado_atendido->prioridade, chamado_atendido->titulo);

    // --- Validação do Novo Status ---
    int novo_status;
    int status_valido = 0;
    do {
        printf("Defina o novo status (1-Aberto, 2-Em Andamento, 3-Fechado): ");
        char buffer_entrada[16];
        if (fgets(buffer_entrada, sizeof(buffer_entrada), stdin) != NULL) {
            char *endptr;
            long valor_lido = strtol(buffer_entrada, &endptr, 10);
            
            if (endptr != buffer_entrada && (*endptr == '\n' || *endptr == '\0') && (valor_lido >= 1 && valor_lido <= 3)) {
                novo_status = (int)valor_lido;
                status_valido = 1;
            } else {
                printf("Opcao invalida! Por favor, insira 1, 2 ou 3.\n");
            }
        }
    } while (!status_valido);
    // --- Fim da Validação ---

    if (novo_status == 3) {
        chamado_atendido->status = FECHADO;
        empilhar(pilha, chamado_atendido);
        printf("Chamado ID %d finalizado e movido para a pilha de concluidos.\n", chamado_atendido->id);
    } else {
        chamado_atendido->status = (novo_status == 2) ? EM_ANDAMENTO : ABERTO;
        enfileirar(fila, chamado_atendido);
        printf("Status do chamado ID %d atualizado e ele retornou para a fila.\n", chamado_atendido->id);
        registrar_log("Chamado re-enfileirado apos atendimento parcial.");
    }
}

void buscar_chamado_por_id(const Fila *fila, const Pilha *pilha) {
    int id_busca;
    // --- Validação do ID ---
    int id_valido = 0;
    do {
        printf("Digite o ID do chamado a ser buscado: ");
        char buffer_entrada[16];
        if (fgets(buffer_entrada, sizeof(buffer_entrada), stdin) != NULL) {
            char *endptr;
            long valor_lido = strtol(buffer_entrada, &endptr, 10);
            
            if (endptr != buffer_entrada && (*endptr == '\n' || *endptr == '\0') && valor_lido > 0) {
                id_busca = (int)valor_lido;
                id_valido = 1;
            } else {
                printf("ID invalido! Por favor, insira um numero inteiro positivo.\n");
            }
        }
    } while (!id_valido);
    // --- Fim da Validação ---

    char log_msg[100];
    sprintf(log_msg, "Iniciando busca pelo chamado ID %d.", id_busca);
    registrar_log(log_msg);

    Chamado* encontrado = buscar_na_fila_recursivo(fila->inicio, id_busca);

    if (encontrado != NULL) {
        printf("\n--- Chamado Encontrado na Fila de Atendimento ---\n");
        printf("ID: %d | Titulo: %s | Prioridade: %d | Status: %s\n",
               encontrado->id, encontrado->titulo, encontrado->prioridade, status_para_string(encontrado->status));
        registrar_log("Chamado encontrado na fila.");
        return;
    }
    
    encontrado = buscar_na_pilha_recursivo(pilha->topo, id_busca);

    if (encontrado != NULL) {
        printf("\n--- Chamado Encontrado na Pilha de Finalizados ---\n");
        printf("ID: %d | Titulo: %s | Prioridade: %d | Status: %s\n",
               encontrado->id, encontrado->titulo, encontrado->prioridade, status_para_string(encontrado->status));
        registrar_log("Chamado encontrado na pilha.");
        return;
    }
    
    printf("Chamado com ID %d nao foi encontrado.\n", id_busca);
    registrar_log("Chamado nao encontrado em nenhuma das estruturas.");
}

void exibir_estatisticas(const Fila *fila, const Pilha *pilha) {
    int abertos = 0, em_andamento = 0;
    FilaNode* mais_antigo_node = NULL;
    
    FilaNode *atual = fila->inicio;
    while(atual != NULL) {
        if(atual->chamado->status == ABERTO) {
            abertos++;
            if (mais_antigo_node == NULL) {
                mais_antigo_node = atual;
            }
        } else if (atual->chamado->status == EM_ANDAMENTO) {
            em_andamento++;
        }
        atual = atual->proximo;
    }

    int fechados = pilha->total_chamados;
    int total = abertos + em_andamento + fechados;
    float percentual_concluidos = (total > 0) ? ((float)fechados / total) * 100.0f : 0;
    
    printf("\n--- Estatisticas ---\n");
    printf("Total de chamados em aberto: %d\n", abertos);
    printf("Total de chamados em andamento: %d\n", em_andamento);
    printf("Total de chamados fechados: %d\n", fechados);
    printf("Percentual de chamados concluidos: %.2f%%\n", percentual_concluidos);

    if (mais_antigo_node != NULL) {
        printf("Chamado mais antigo ainda aberto: ID %d - '%s'\n", mais_antigo_node->chamado->id, mais_antigo_node->chamado->titulo);
    } else {
        printf("Nao ha chamados abertos.\n");
    }
    printf("--------------------\n");
    
    registrar_log("Relatorio de estatisticas gerado.");
}
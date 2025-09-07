#ifndef UTILS_H
#define UTILS_H

#include "fila.h"
#include "pilha.h"

// Exibe o menu principal de opções.
void exibir_menu();

// Limpa o buffer de entrada do teclado.
void limpar_buffer_teclado();

// Solicita e cadastra um novo chamado.
void cadastrar_novo_chamado(Fila *fila, int *proximo_id);

// Executa o atendimento do chamado de maior prioridade.
void executar_atendimento_chamado(Fila *fila, Pilha *pilha);

// Realiza a busca por um chamado usando o ID.
void buscar_chamado_por_id(const Fila *fila, const Pilha *pilha);

// Calcula e exibe as estatísticas dos chamados.
void exibir_estatisticas(const Fila *fila, const Pilha *pilha);

#endif // UTILS_H
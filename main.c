#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Necessário para strtol

#include "fila.h"
#include "pilha.h"
#include "log.h"
#include "utils.h"

int main() {
    iniciar_log();

    Fila *fila_chamados = criar_fila();
    Pilha *pilha_finalizados = criar_pilha();
    int proximo_id = 1;
    int opcao = 0; // Inicializa com um valor neutro

    do {
        exibir_menu();

        char buffer_entrada[16];
        // Lê a linha inteira para o buffer para evitar erros de scanf
        if (fgets(buffer_entrada, sizeof(buffer_entrada), stdin) != NULL) {
            char *endptr;
            // Tenta converter o início do buffer para um número
            long valor_lido = strtol(buffer_entrada, &endptr, 10);

            // Validação:
            // 1. O ponteiro 'endptr' não pode ser o mesmo do início (nenhum número lido).
            // 2. O caractere onde a conversão parou deve ser uma quebra de linha ('\n').
            if (endptr == buffer_entrada || (*endptr != '\n' && *endptr != '\0')) {
                printf("Entrada invalida! Por favor, digite apenas um numero.\n\n");
                opcao = 0; // Define uma opção inválida para repetir o menu
            } else {
                opcao = (int)valor_lido; // Conversão bem-sucedida
            }
        }

        switch (opcao) {
            case 1:
                cadastrar_novo_chamado(fila_chamados, &proximo_id);
                break;
            case 2:
                printf("Qual status deseja filtrar? (0-Todos, 1-Aberto, 2-Em Andamento, 3-Fechado): ");
                int filtro_int;
                // Validação similar para a entrada do filtro
                if (fgets(buffer_entrada, sizeof(buffer_entrada), stdin) != NULL) {
                    char *endptr_filtro;
                    long filtro_lido = strtol(buffer_entrada, &endptr_filtro, 10);
                    if (endptr_filtro == buffer_entrada || (*endptr_filtro != '\n' && *endptr_filtro != '\0')) {
                        printf("Entrada de filtro invalida! Mostrando todos.\n");
                        filtro_int = 0;
                    } else {
                        filtro_int = (int)filtro_lido;
                    }
                } else {
                    filtro_int = 0; // Padrão em caso de erro
                }

                if (filtro_int >= 0 && filtro_int <= 2) {
                    listar_chamados_fila(fila_chamados, (StatusChamado)filtro_int);
                }
                if (filtro_int == 0 || filtro_int == 3) {
                     listar_chamados_pilha(pilha_finalizados);
                }
                break;
            case 3:
                executar_atendimento_chamado(fila_chamados, pilha_finalizados);
                break;
            case 4:
                buscar_chamado_por_id(fila_chamados, pilha_finalizados);
                break;
            case 5:
                exibir_estatisticas(fila_chamados, pilha_finalizados);
                break;
            case 6:
                printf("Finalizando o programa...\n");
                exibir_estatisticas(fila_chamados, pilha_finalizados);
                break;
            case 0:
                // Caso da entrada inválida, apenas continua o loop para mostrar o menu de novo
                break; 
            default:
                printf("Opcao invalida! Escolha um numero entre 1 e 6.\n\n");
        }

    } while (opcao != 6);
    
    // Liberação de toda a memória alocada
    liberar_fila(fila_chamados);
    liberar_pilha(pilha_finalizados);

    fechar_log();

    return 0;
}
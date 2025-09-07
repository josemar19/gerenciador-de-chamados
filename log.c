#include "log.h"
#include <time.h>
#include <stdlib.h>

static FILE *arquivo_log = NULL;

void iniciar_log() {
    // "a" abre para adicionar ao final do arquivo. Se não existir, ele é criado.
    arquivo_log = fopen("log.txt", "a");
    if (arquivo_log == NULL) {
        perror("Erro ao abrir o arquivo de log. O log não será registrado.");
        exit(1); // Encerra se não for possível criar o log.
    }
    
    time_t t = time(NULL);
    fprintf(arquivo_log, "\n--- SESSÃO INICIADA EM: %s ---\n", ctime(&t));
}

void registrar_log(const char *mensagem) {
    if (arquivo_log != NULL) {
        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);
        char buffer_tempo[26];
        strftime(buffer_tempo, 26, "%Y-%m-%d %H:%M:%S", tm_info);
        
        fprintf(arquivo_log, "[%s] %s\n", buffer_tempo, mensagem);
        fflush(arquivo_log); // Garante que a mensagem seja escrita imediatamente.
    }
}

void fechar_log() {
    if (arquivo_log != NULL) {
        registrar_log("Fim do programa. Fechando log.");
        fprintf(arquivo_log, "--- SESSÃO FINALIZADA ---\n");
        fclose(arquivo_log);
    }
}
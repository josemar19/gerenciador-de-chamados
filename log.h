#ifndef LOG_H
#define LOG_H

#include <stdio.h>

// Abre (ou cria) o arquivo de log para escrita.
void iniciar_log();

// Registra uma mensagem no arquivo de log.
void registrar_log(const char *mensagem);

// Fecha o arquivo de log.
void fechar_log();

#endif // LOG_H
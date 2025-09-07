# gerenciador-de-chamados
um gerenciador de chamados de suporte ao atendimento
# Sistema de Gerenciamento de Chamados

## Descrição do Projeto

Este é um projeto acadêmico da disciplina de Linguagem de Programação do Instituto Federal da Bahia (IFBA) - Campus Santo Antônio de Jesus. O objetivo é desenvolver um sistema em C para gerenciar chamados de suporte técnico, aplicando conceitos avançados de programação como estruturas de dados dinâmicas (filas e pilhas), alocação dinâmica de memória, modularização de código, tratamento de erros e depuração.

O sistema simula o fluxo de um helpdesk, permitindo cadastrar, listar, atender e buscar chamados, além de gerar estatísticas sobre as operações.

## Funcionalidades Principais

* **Cadastrar Chamado**: Adiciona um novo chamado com ID, título, prioridade (1-5) e status a uma fila de atendimento.
* **Listar Chamados**: Exibe todos os chamados, permitindo filtrar por status (Aberto, Em Andamento, Fechado).
* **Executar Atendimento**: Remove o chamado de maior prioridade (menor número) da fila para ser atendido. Se o status for alterado para "Fechado", o chamado é movido para uma pilha de finalizados.
* **Buscar Chamado**: Utiliza uma função recursiva para buscar um chamado por ID na fila de atendimento ou na pilha de finalizados.
* **Exibir Estatísticas**: Mostra o total de chamados por status, o chamado mais antigo ainda em aberto e o percentual de chamados concluídos.
* **Logs e Tratamento de Erros**: Todas as operações importantes são registradas em um arquivo `log.txt`. O sistema também utiliza `assert` para verificar condições críticas.

## Estrutura do Projeto

O código é organizado de forma modular para facilitar a manutenção e a legibilidade.

```
/gerenciamento_chamados
|-- include/           # Arquivos de cabeçalho (.h)
|   |-- fila.h
|   |-- pilha.h
|   |-- log.h
|   |-- utils.h
|-- src/               # Arquivos de código-fonte (.c)
|   |-- main.c
|   |-- fila.c
|   |-- pilha.c
|   |-- log.c
|   |-- utils.c
|-- bin/               # Diretório para o executável (criado na compilação)
|-- obj/               # Diretório para arquivos objeto (criado na compilação)
|-- Makefile           # Arquivo para automatizar a compilação
|-- README.md          # Este arquivo
|-- log.txt            # Arquivo de log gerado durante a execução
```

## Requisitos

* Compilador C GCC 
* Utilitário `make`

## Como Compilar e Executar

### 1. Clonar o Repositório

```bash
git clone <URL_DO_SEU_REPOSITORIO_GIT>
cd gerenciamento_chamados
```

### 2. Compilar o Projeto

Para compilar o projeto, utilize o `Makefile` fornecido. Navegue até o diretório raiz do projeto e execute o comando:

```bash
make
```

Este comando irá compilar todos os arquivos-fonte do diretório `src/` e criar o executável `gerenciamento_chamados` dentro do diretório `bin/`.

### 3. Executar o Programa

Após a compilação, execute o programa com o seguinte comando:

```bash
./bin/gerenciamento_chamados
```

Você também pode usar um atalho que compila e executa em um único passo:

```bash
make run
```

### 4. Limpar os Arquivos Gerados

Para remover o executável e todos os arquivos objeto (`.o`) gerados durante a compilação, utilize o comando:

```bash
make clean
```

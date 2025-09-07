# Nome do compilador
CC = gcc

# Flags de compilação: -I para diretórios de include, -Wall para warnings, -g para debug
CFLAGS = -Iinclude -Wall -g

# Diretórios
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

# Arquivos fonte .c
SOURCES = $(wildcard $(SRCDIR)/*.c)

# Arquivos objeto .o (são criados no diretório obj/)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

# Nome do executável final
TARGET = $(BINDIR)/gerenciamento_chamados

# --- Regras Principais ---

# Regra principal: criar o executável
all: $(TARGET)

$(TARGET): $(OBJECTS)
	-@if not exist $(subst /,\,$(BINDIR)) mkdir $(subst /,\,$(BINDIR))
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Executavel '$(TARGET)' criado com sucesso."

# Regra para compilar cada .c em seu respectivo .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	-@if not exist $(subst /,\,$(OBJDIR)) mkdir $(subst /,\,$(OBJDIR))
	$(CC) $(CFLAGS) -c -o $@ $<

# Regra 'run' para compilar e executar
run: all
	@echo "Executando o programa..."
ifeq ($(OS),Windows_NT)
	$(subst /,\,$(TARGET))
else
	./$(TARGET)
endif

# ---Limpeza  ---

# O comando 'clean' que realiza a limpeza dos arquivos gerados
clean:
ifeq ($(OS),Windows_NT)
	mingw32-make clean-windows
else
	make clean-unix
endif

# limpando os arquivos .o gerados
clean-windows:
	@echo "Limpando arquivos gerados (Windows)..."
	-if exist log.txt del log.txt
	-if exist $(subst /,\,$(OBJDIR)) rmdir /S /Q $(subst /,\,$(OBJDIR))
	-if exist $(subst /,\,$(BINDIR)) rmdir /S /Q $(subst /,\,$(BINDIR))
	@echo "Limpeza concluida."


# Declara os alvos que não geram arquivos
.PHONY: all clean run clean-windows
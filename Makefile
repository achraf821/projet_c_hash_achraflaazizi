# ========================
#  Projet : Générateur & Lookup de condensats (C)
#  Auteur : Achraf LAAZIZI
#  ========================

CC = gcc
CFLAGS = -std=c17 -O2 -Wall -Wextra -Isrc
LDFLAGS = -lcrypto
SRC_DIR = src
OBJ_DIR = obj
BIN = prog

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# === Règles principales ===

all: $(BIN)

$(BIN): $(OBJ)
	@echo "🔧 Édition des liens..."
	$(CC) $(OBJ) -o $@ $(LDFLAGS)
	@echo "✅ Compilation terminée : ./prog prêt à l’emploi"

# === Compilation des .o ===

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "⚙️  Compilation de $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# === Nettoyage ===

clean:
	@echo "🧹 Suppression des fichiers objets..."
	rm -rf $(OBJ_DIR)

fclean: clean
	@echo "🗑️  Suppression de l’exécutable..."
	rm -f $(BIN)

re: fclean all

# === Aide ===

help:
	@echo "Commandes disponibles :"
	@echo "  make        → compile le projet"
	@echo "  make clean  → supprime les fichiers objets"
	@echo "  make fclean → supprime les objets + exécutable"
	@echo "  make re     → recompile tout"

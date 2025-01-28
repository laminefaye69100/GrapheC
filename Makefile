# Définition du compilateur et des options de compilation
CXX = g++                              # Utilise g++ comme compilateur
CXXFLAGS = -Wall -Wextra -O2 -MMD      # Options pour afficher les avertissements, optimiser le code et générer des fichiers de dépendance

# Fichiers sources et fichiers objets correspondants
SRC = pixel.cpp graphe.cpp main.cpp  # Liste des fichiers source
OBJ = $(SRC:.cpp=.o)                      # Génère les fichiers objets à partir des fichiers sources
DEP = $(SRC:.cpp=.d)                      # Génère les fichiers de dépendance

# Nom de l'exécutable
EXEC = programme_executable               # Nom de l'exécutable final

# Cible par défaut
all: $(EXEC)                             # La cible 'all' dépend de l'exécutable

# Règle pour construire l'exécutable
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^          # Compile les fichiers objets en un exécutable

# Règle pour compiler les fichiers source en fichiers objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@       # Compile chaque fichier .cpp en .o

# Inclusion des fichiers de dépendance
-include $(DEP)                         # Inclut les fichiers de dépendance pour gérer les changements de fichiers

# Règle de nettoyage pour supprimer les fichiers objets et l'exécutable
.PHONY: clean                           # Déclare 'clean' comme une cible phony
clean:
	rm -f $(OBJ) $(DEP) $(EXEC)          # Supprime les fichiers objets, les fichiers de dépendance et l'exécutable

# Règle pour exécuter le programme
.PHONY: run                             # Déclare 'run' comme une cible phony
run: $(EXEC)
	./$(EXEC)                            # Exécute le programme compilé

# Les cibles clean et run ont été déclarées comme .PHONY, 
#ce qui informe make qu'elles ne correspondent pas à des fichiers.
# Compilateur et options
CXX = g++
CXXFLAGS = -I./class -std=c++11

# Répertoires
CLASSDIR = class

# Fichiers sources des classes
MODEL_SRC = $(CLASSDIR)/Model.cpp
# Règle par défaut
all: test1 

# Test 1 - Classe Model
test1: Test1.cpp $(MODEL_SRC) $(CLASSDIR)/Model.h
	$(CXX) $(CXXFLAGS) -o test1 Test1.cpp $(MODEL_SRC)

# Nettoyage
clean:
	rm -f test1 

# Règles pour compiler individuellement
.PHONY: all clean
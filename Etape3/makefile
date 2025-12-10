# Compilateur et options
CXX = g++
CXXFLAGS = -I./class -std=c++11

# Répertoires
CLASSDIR = class

# Fichiers sources des classes
MODEL_SRC = $(CLASSDIR)/Model.cpp
OPTION_SRC = $(CLASSDIR)/Option.cpp
CAR_SRC = $(CLASSDIR)/Car.cpp


# Règle par défaut
all: test1 test2a test2b test2c test3 

# Test 1 - Classe Model
test1: Test1.cpp $(MODEL_SRC) $(CLASSDIR)/Model.h
	$(CXX) $(CXXFLAGS) -o test1 Test1.cpp $(MODEL_SRC)

# Test 2a - Car sans options
test2a: Test2a.cpp $(MODEL_SRC) $(CAR_SRC) $(OPTION_SRC) $(CLASSDIR)/Model.h $(CLASSDIR)/Car.h $(CLASSDIR)/Option.h
	$(CXX) $(CXXFLAGS) -o test2a Test2a.cpp $(MODEL_SRC) $(CAR_SRC) $(OPTION_SRC)

# Test 2b - Option seule
test2b: Test2b.cpp $(OPTION_SRC) $(CLASSDIR)/Option.h
	$(CXX) $(CXXFLAGS) -o test2b Test2b.cpp $(OPTION_SRC)

# Test 2c - Car avec options
test2c: Test2c.cpp $(MODEL_SRC) $(CAR_SRC) $(OPTION_SRC) $(CLASSDIR)/Model.h $(CLASSDIR)/Car.h $(CLASSDIR)/Option.h
	$(CXX) $(CXXFLAGS) -o test2c Test2c.cpp $(MODEL_SRC) $(CAR_SRC) $(OPTION_SRC)

# Test 3 - Surcharge des opérateurs
test3: Test3.cpp $(MODEL_SRC) $(CAR_SRC) $(OPTION_SRC) $(CLASSDIR)/Model.h $(CLASSDIR)/Car.h $(CLASSDIR)/Option.h
	$(CXX) $(CXXFLAGS) -o test3 Test3.cpp $(MODEL_SRC) $(CAR_SRC) $(OPTION_SRC)

# Nettoyage
clean:
	rm -f test1 test2a test2b test2c test3 

# Règles pour compiler individuellement
.PHONY: all clean
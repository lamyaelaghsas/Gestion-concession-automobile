# Compilateur et options
CXX = g++
CXXFLAGS = -I./class -std=c++11 -Wall

# Répertoires
CLASSDIR = class

# Fichiers sources des classes
OPTION_SRC = $(CLASSDIR)/Option.cpp
MODEL_SRC = $(CLASSDIR)/Model.cpp
CAR_SRC = $(CLASSDIR)/Car.cpp
PERSON_SRC = $(CLASSDIR)/Person.cpp
ACTOR_SRC = $(CLASSDIR)/Actor.cpp
CLIENT_SRC = $(CLASSDIR)/Client.cpp
EMPLOYEE_SRC = $(CLASSDIR)/Employee.cpp
GARAGE_SRC = $(CLASSDIR)/Garage.cpp
EXCEPTION_SRC = $(CLASSDIR)/Exception.cpp
OPTIONEXCEPTION_SRC = $(CLASSDIR)/OptionException.cpp
PASSWORDEXCEPTION_SRC = $(CLASSDIR)/PasswordException.cpp

# Règle par défaut
all: test8a

# Test 8a - Classe Garage avec conteneurs STL
test8a: Test8a.cpp $(OPTION_SRC) $(MODEL_SRC) $(CAR_SRC) $(CLIENT_SRC) $(EMPLOYEE_SRC) \
        $(ACTOR_SRC) $(PERSON_SRC) $(GARAGE_SRC) $(EXCEPTION_SRC) $(OPTIONEXCEPTION_SRC) \
        $(PASSWORDEXCEPTION_SRC) \
        $(CLASSDIR)/Option.h $(CLASSDIR)/Model.h $(CLASSDIR)/Car.h $(CLASSDIR)/Client.h \
        $(CLASSDIR)/Employee.h $(CLASSDIR)/Actor.h $(CLASSDIR)/Person.h $(CLASSDIR)/Garage.h \
        $(CLASSDIR)/Exception.h $(CLASSDIR)/OptionException.h $(CLASSDIR)/PasswordException.h
	$(CXX) $(CXXFLAGS) -o test8a Test8a.cpp $(OPTION_SRC) $(MODEL_SRC) $(CAR_SRC) \
	                     $(CLIENT_SRC) $(EMPLOYEE_SRC) $(ACTOR_SRC) $(PERSON_SRC) \
	                     $(GARAGE_SRC) $(EXCEPTION_SRC) $(OPTIONEXCEPTION_SRC) \
	                     $(PASSWORDEXCEPTION_SRC)

# Nettoyage
clean:
	rm -f test8a

# Nettoyer complètement
cleanall: clean

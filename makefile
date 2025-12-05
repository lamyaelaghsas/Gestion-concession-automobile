# Compilateur et options
CXX = g++
CXXFLAGS = -I./class -std=c++11

# Répertoires
CLASSDIR = class

# Fichiers sources des classes
MODEL_SRC = $(CLASSDIR)/Model.cpp
OPTION_SRC = $(CLASSDIR)/Option.cpp
CAR_SRC = $(CLASSDIR)/Car.cpp
PERSON_SRC = $(CLASSDIR)/Person.cpp
ACTOR_SRC = $(CLASSDIR)/Actor.cpp
EMPLOYEE_SRC = $(CLASSDIR)/Employee.cpp
CLIENT_SRC = $(CLASSDIR)/Client.cpp
EXCEPTION_SRC = $(CLASSDIR)/Exception.cpp
OPTIONEXCEPTION_SRC = $(CLASSDIR)/OptionException.cpp
PASSWORDEXCEPTION_SRC = $(CLASSDIR)/PasswordException.cpp

# Règle par défaut
all: test1 test2a test2b test2c test3 test4 test5

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

# Test 4 - Héritage et classes abstraites
test4: Test4.cpp $(PERSON_SRC) $(ACTOR_SRC) $(EMPLOYEE_SRC) $(CLIENT_SRC) $(CLASSDIR)/Person.h $(CLASSDIR)/Actor.h $(CLASSDIR)/Employee.h $(CLASSDIR)/Client.h
	$(CXX) $(CXXFLAGS) -o test4 Test4.cpp $(PERSON_SRC) $(ACTOR_SRC) $(EMPLOYEE_SRC) $(CLIENT_SRC)

# Test 5 - Les exceptions
test5: Test5.cpp $(OPTION_SRC) $(CAR_SRC) $(MODEL_SRC) $(EMPLOYEE_SRC) $(ACTOR_SRC) $(PERSON_SRC) $(EXCEPTION_SRC) $(OPTIONEXCEPTION_SRC) $(PASSWORDEXCEPTION_SRC) \
       $(CLASSDIR)/Option.h $(CLASSDIR)/Car.h $(CLASSDIR)/Model.h $(CLASSDIR)/Employee.h $(CLASSDIR)/Actor.h $(CLASSDIR)/Person.h \
       $(CLASSDIR)/Exception.h $(CLASSDIR)/OptionException.h $(CLASSDIR)/PasswordException.h
	$(CXX) $(CXXFLAGS) -o test5 Test5.cpp $(OPTION_SRC) $(CAR_SRC) $(MODEL_SRC) $(EMPLOYEE_SRC) $(ACTOR_SRC) $(PERSON_SRC) \
	                     $(EXCEPTION_SRC) $(OPTIONEXCEPTION_SRC) $(PASSWORDEXCEPTION_SRC)

# Nettoyage
clean:
	rm -f test1 test2a test2b test2c test3 test4 test5

# Règles pour compiler individuellement
.PHONY: all clean
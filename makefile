SRC = src
INC = include

OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -Wall -g -fopenmp -I$(INC) -c --std=c++14

all:$(BIN)/main 
	
# ************ Compilación de módulos ************

$(BIN)/main: $(OBJ)/main.o $(OBJ)/complex_n.o $(OBJ)/bitmap.o $(OBJ)/color.o
	$(CXX) -o $(BIN)/main -fopenmp $(OBJ)/main.o $(OBJ)/complex_n.o \
	$(OBJ)/bitmap.o $(OBJ)/color.o

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/complex_n.h $(INC)/bitmap.h 
	$(CXX) $(CPPFLAGS)  $(SRC)/main.cpp -o  $(OBJ)/main.o 

$(OBJ)/bitmap.o: $(SRC)/bitmap.cpp $(INC)/bitmap.h
	$(CXX) $(CPPFLAGS)  $(SRC)/bitmap.cpp -o  $(OBJ)/bitmap.o	

$(OBJ)/complex_n.o: $(SRC)/complex_n.cpp $(INC)/complex_n.h 
	$(CXX) $(CPPFLAGS)  $(SRC)/complex_n.cpp -o  $(OBJ)/complex_n.o

$(OBJ)/color.o: $(SRC)/color.cpp $(INC)/color.h
	$(CXX) $(CPPFLAGS) $(SRC)/color.cpp -o $(OBJ)/color.o



# ************ Limpieza ************
clean :
	-rm $(OBJ)/*

mrproper : clean
	-rm $(BIN)/* 

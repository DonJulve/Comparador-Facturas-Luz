################################################################################
## Fichero «Makefile» para el programa del trabajo obligatorio
################################################################################

################################################################################
## Declaracion de variables del fichero «Makefile»

## DIRECTORIOS
SOURCE_DIR = src
BUILD_DIR = build
BIN_DIR = bin

VPATH = $(SOURCE_DIR) 

## COMPILADOR Y OPCIONES DE COMPILACIÓN:
CXX = g++
CXXFLAGS = -g -Wall -Wextra


## FICHEROS OBJETO (RESULTADOS INTERMEDIOS DE COMPILACIÓN):
OBJECTS =  $(addprefix $(BUILD_DIR)/, main.o fecha.o gasto-diario.o \
                       fichs-electricos.o vector-gastos.o tarifas-comerciales.o)

################################################################################
## Reglas del fichero «Makefile»

all: $(OBJECTS) | $(BIN_DIR)
	$(CXX) -o $(BIN_DIR)/electricidad $^ -g

$(BUILD_DIR)/%.o: %.cpp fecha.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@  

$(BUILD_DIR)/main.o:                gasto-diario.hpp fichs-electricos.hpp vector-gastos.hpp tarifas-comerciales.hpp
$(BUILD_DIR)/gasto-diario.o:        gasto-diario.hpp
$(BUILD_DIR)/fichs-electricos.o:    gasto-diario.hpp fichs-electricos.hpp
$(BUILD_DIR)/vector-gastos.o:       gasto-diario.hpp vector-gastos.hpp
$(BUILD_DIR)/tarifas-comerciales.o: gasto-diario.hpp tarifas-comerciales.hpp

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean:
ifeq ($(OS),Windows_NT)
	if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)
	if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)
else
	rm -f $(OBJECTS) $(BIN_DIR)/*
endif

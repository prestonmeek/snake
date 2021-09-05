SRC_DIR := ./src
INC_DIR := ./include
OBJ_DIR := ./obj
LIB_DIR := ./lib

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
INC_FILES := $(wildcard $(INC_DIR)/*.h)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

CFLAGS = -I$(INC_DIR) -std=c++17
LFLAGS = -lSDL2 -lSDL2_ttf

main: $(OBJ_FILES)
	g++ $(LFLAGS) -o $@ $^

# maybe clean up the stuff below? idrk how makefiles work

# obj files need updated src and header file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.h
	g++ -c -o $@ $< $(CFLAGS)

# main obj file only needs updated src file (main.h doesn't exist)
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	g++ -c -o $@ $< $(CFLAGS)

clean:
	rm obj/*.o main
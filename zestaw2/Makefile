CC = g++
CFLAGS = -Wall -std=c++11

NAME=zestaw2
OBJ_DIR = obj
SRC_DIR = src
BIN_DIR = bin
INC_DIR = $(SRC_DIR)/include

OUT = main
BINARIES = $(addprefix $(BIN_DIR)/, $(OUT))
DEPS = test
DEPS_OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(DEPS)))
DEPS_INC = $(addprefix $(INC_DIR), $(addsuffix .h, $(DEPS)))
SORTING_ALGS = quicksort bubblesort
DEPS_INC = $(addprefix $(INC_DIR), $(addsuffix .h, $(SORTING_ALGS)))

.PRECIOUS: $(OBJ_DIR)/%.o
.PHONY: clean all structure run
all: $(BINARIES)

$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(DEPS_OBJ) | structure
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.h $(SORTING_ALGS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
run: all
	./$(BIN_DIR)/$(OUT)
structure:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)
zip: clean
	zip -r ../$(NAME).zip ../$(NAME)

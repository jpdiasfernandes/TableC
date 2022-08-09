CC      := gcc
CCFLAGS := -O2
DEBUG   := -g -ggdb -DDEBUG
FLAGS   = -Wall -Wextra


MAIN        := tablec
SRC_DIR     := src
OBJ_DIR     := obj
BIN_DIR     := bin
INCLUDE_DIR := includes
SRC         := $(wildcard $(SRC_DIR)/*.c)
INCLUDE     := -iquote $(INCLUDE_DIR)
INCLUDE     := $(INCLUDE) `pkg-config --cflags --libs glib-2.0`
OBJ         := $(addprefix $(OBJ_DIR)/, $(notdir $(patsubst %.c, %.o, $(SRC))))


.DEFAULT_GOAL = build
.PHONY: clean run build debug struct

vpath %.c $(SRC_DIR)

$(OBJ_DIR)/%.o : %.c
	$(CC) -c $(INCLUDE) $(FLAGS) $^ -o $@

$(MAIN): $(OBJ)
	$(CC) $(INCLUDE) $(FLAGS) $^ -o $(BIN_DIR)/$@

build: FLAGS += $(CCFLAGS)
build: $(MAIN)

struct:
	mkdir $(OBJ_DIR) $(BIN_DIR)

run: build
	./$(BIN_DIR)/$(MAIN)

debug: FLAGS += $(DEBUG)
debug: $(MAIN)

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/*

.PHONY: all clean lint

CC ?= gcc
CFLAGS = -W -Wall -pedantic -std=c99
CPPFLAGS = -D_POSIX_C_SOURCE=200809L
LDFLAGS = -lc

SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
BIN =\
	 $(BIN_DIR)/hello\
	 $(BIN_DIR)/filemode\
	 $(BIN_DIR)/remove\
	 $(BIN_DIR)/read
OUT = newFile.txt

all: $(BIN)
	@echo all built

clean:
	@rm -rf $(BUILD_DIR) $(OUT)

lint:
	@cpplint --recursive $(SRC_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(BIN_DIR)/%: $(OBJ_DIR)/%.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

# Chapter 2
$(OBJ_DIR)/hello.o: $(SRC_DIR)/hello.c
$(BIN_DIR)/hello: $(OBJ_DIR)/hello.o

# Chapter 3
$(OBJ_DIR)/filemode.o: $(SRC_DIR)/filemode.c
$(BIN_DIR)/filemode: $(OBJ_DIR)/filemode.o

# Chapter 4
$(OBJ_DIR)/remove.o: $(SRC_DIR)/remove.c
$(BIN_DIR)/remove: $(OBJ_DIR)/remove.o

# Chapter 5
$(OBJ_DIR)/read.o: $(SRC_DIR)/read.c
$(BIN_DIR)/read: $(OBJ_DIR)/read.o

.PHONY: all clean lint

CC ?= gcc
CFLAGS = -W -Wall -pedantic -std=c99
CPPFLAGS = -D_POSIX_C_SOURCE=200809L
LDFLAGS = -lc -lpthread

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
	 $(BIN_DIR)/read\
	 $(BIN_DIR)/write1\
	 $(BIN_DIR)/write2\
	 $(BIN_DIR)/two_instances\
	 $(BIN_DIR)/execv_example\
	 $(BIN_DIR)/simple_fork\
	 $(BIN_DIR)/threads\
	 $(BIN_DIR)/threads2
OUT = newFile.txt myFile.txt modified_text.txt

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
	$(CC) -o $@ $^ $(LDFLAGS)

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

# Chapter 6
$(OBJ_DIR)/write1.o: $(SRC_DIR)/write1.c
$(BIN_DIR)/write1: $(OBJ_DIR)/write1.o

$(OBJ_DIR)/write2.o: $(SRC_DIR)/write2.c
$(BIN_DIR)/write2: $(OBJ_DIR)/write2.o

# Chapter 8
$(OBJ_DIR)/two_instances.o: $(SRC_DIR)/two_instances.c
$(BIN_DIR)/two_instances: $(OBJ_DIR)/two_instances.o

# Chapter 9
$(OBJ_DIR)/execv_example.o: $(SRC_DIR)/execv_example.c
$(BIN_DIR)/execv_example: $(OBJ_DIR)/execv_example.o

$(OBJ_DIR)/simple_fork.o: $(SRC_DIR)/simple_fork.c
$(BIN_DIR)/simple_fork: $(OBJ_DIR)/simple_fork.o

# Chapter 10
$(OBJ_DIR)/threads.o: $(SRC_DIR)/threads.c
$(BIN_DIR)/threads: $(OBJ_DIR)/threads.o

$(OBJ_DIR)/threads2.o: $(SRC_DIR)/threads2.c
$(BIN_DIR)/threads2: $(OBJ_DIR)/threads2.o

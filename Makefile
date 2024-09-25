.PHONY: all clean

CC ?= gcc
CFLAGS = -W -Wall -pedantic -std=c99
CPPFLAGS = -D_POSIX_C_SOURCE=200809L
LDFLAGS = -lc

SRC_DIR = src
BUILD_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))
BIN = hello

all: $(BIN)
	@echo all built

clean:
	@rm -rf $(BIN) $(BUILD_DIR)

$(OBJ): $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(BIN): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/hello.o: $(SRC_DIR)/hello.c
hello: $(BUILD_DIR)/hello.o


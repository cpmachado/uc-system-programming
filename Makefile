.PHONY: all clean

CC ?= gcc
CFLAGS = -W -Wall -pedantic -std=c99
CPPFLAGS = -D_POSIX_C_SOURCE=200809L
LDFLAGS = -lc

SRC_DIR = src
BUILD_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))
BIN = hello filemode
OUT = newFile.txt

all: $(BIN)
	@echo all built

clean:
	@rm -rf $(BIN) $(BUILD_DIR) $(OUT)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

%: $(BUILD_DIR)/%.o
	$(CC) $(LDFLAGS) -o $@ $^

# Chapter 2
$(BUILD_DIR)/hello.o: $(SRC_DIR)/hello.c
hello: $(BUILD_DIR)/hello.o

# Chapter 3
$(BUILD_DIR)/filemode.o: $(SRC_DIR)/filemode.c
filemode: $(BUILD_DIR)/filemode.o

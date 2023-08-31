CC := gcc
DEBUGGER := gdb
INCLUDE := -Iinclude
PRIV_INCLUDE := -Isrc/include
CSTD := -std=c99
CFLAGS := -g3 -Wall -Werror -Wextra -pedantic

SRC := src
SRC_FILES := $(wildcard $(SRC)/*.c)
BUILD_DIR := build
OBJ_FILES := $(patsubst $(SRC)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
TEST_DATA_DIR := test-data

PROJECT := posix-regex

.PHONY: all debug run $(BUILD_DIR)/$(TEST_DATA_DIR) $(BUILD_DIR) clean

all: run

debug: $(BUILD_DIR)/$(PROJECT) | $(BUILD_DIR)/$(TEST_DATA_DIR)
	@$(DEBUGGER) ./$(BUILD_DIR)/$(PROJECT)

run: $(BUILD_DIR)/$(PROJECT) | $(BUILD_DIR)/$(TEST_DATA_DIR)
	@./$(BUILD_DIR)/$(PROJECT)

$(BUILD_DIR)/$(TEST_DATA_DIR): $(BUILD_DIR)
	@cp -r $(TEST_DATA_DIR) $(BUILD_DIR)/$(TEST_DATA_DIR)

$(BUILD_DIR)/$(PROJECT): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(CSTD) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC)/%.c | $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) $(PRIV_INCLUDE) $(CSTD) -c -o $@ $<

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

clean:
	@rm -rf $(BUILD_DIR)

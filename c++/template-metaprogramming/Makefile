CC := g++
DEBUGGER := gdb
INCLUDE := -Iinclude
CFLAGS := -g3 -Wall -Werror -Wextra -pedantic
CPP_STD := -std=c++17
SRC := src
SRC_FILES := $(wildcard $(SRC)/*.cpp)
BUILD_DIR := build
OBJ_FILES := $(patsubst $(SRC)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

PROJECT := metalivecode

.PHONY: all run debug build $(BUILD_DIR) clean

all: $(BUILD_DIR)/$(PROJECT)

run: $(BUILD_DIR)/$(PROJECT)
	@./$(BUILD_DIR)/$(PROJECT)

debug: $(BUILD_DIR)/$(PROJECT)
	@$(DEBUGGER) @./$(BUILD_DIR)/$(PROJECT)

$(BUILD_DIR)/$(PROJECT): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(INCLUDE) $(CPP_STD) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC)/%.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(CPP_STD) -c -o $@ $<

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

clean:
	@rm -rf $(BUILD_DIR)

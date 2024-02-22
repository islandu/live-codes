# Project info
PROJECT := fib64
PYMOD := $(PROJECT)py
SHARED_LIB := lib$(PROJECT).so
STATIC_LIB := lib$(PROJECT).a

# Compilation commands and options
CC := gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
STD = gnu89
AR := ar
ARFLAGS := -crs
PYTHON := python3
PYMOD_SETUP := setup.py
PYMOD_SETUPFLAGS := -q
# PYMOD_BUILDCMD := $(PYTHON) $(PYMOD_SETUP) $(PYMOD_SETUPFLAGS) build_ext


# Codebase structure
INCLUDE := include
SRC := src
LIB_SRC := $(filter-out %py.c,$(wildcard $(SRC)/*.c))
PYMOD_SRC := $(SRC)/$(PYMOD).c

# Build structure
BUILD := build
BUILD_LIB := $(BUILD)/lib
BUILD_SHARED := $(BUILD)/obj/shared
BUILD_STATIC := $(BUILD)/obj/static
SHARED_OBJS := $(patsubst $(SRC)/%.c,$(BUILD_SHARED)/%.o,$(LIB_SRC))
STATIC_OBJS := $(patsubst $(SRC)/%.c,$(BUILD_STATIC)/%.o,$(LIB_SRC))
# PYMOD_ABI := $(shell $(PYTHON) -c 'import sysconfig; print(sysconfig.get_config_var("SOABI"))')
# PYMOD_SHARED_LIB := $(PYMOD).$(PYMOD_ABI).so
PYDIST_VERSION := 0.1
PYDIST := $(PYMOD)-$(PYDIST_VERSION).tar.gz
PYMOD_BUILDCMD := $(PYTHON) -m build --sdist
PYMOD_BUILDOPTS := --outdir $(BUILD)

# Install commands and paths
INSTALL_PREFIX := /usr/local
INSTALL_INCLUDE := $(INSTALL_PREFIX)/include/$(PROJECT)
INSTALL_LIB := $(INSTALL_PREFIX)/lib
PYINSTALL := pip3 install
PYINSTALL_OPTS := --quiet --force-reinstall
PYUNINSTALL := pip3 uninstall
PYUNINSTALL_OPTS := --quiet --yes

# Build targets
.PHONY := all install uninstall $(PYMOD) static shared clean $(BUILD) $(BUILD_STATIC) $(BUILD_SHARED)

all: $(PYMOD) static shared

install: $(BUILD_LIB)/$(SHARED_LIB) $(BUILD_LIB)/$(STATIC_LIB) $(BUILD)/$(PYDIST)
	@echo "Installing headers and shared/static libraries..."
	@sudo install -v -d $(INSTALL_INCLUDE)
	@sudo install -v -m 644 $(INCLUDE)/$(PROJECT)/*.h $(INSTALL_INCLUDE)
	@sudo install -v -m 755 $(BUILD_LIB)/lib* $(INSTALL_LIB)
	@echo "Installing python extension module in user site packages..."
	@$(PYINSTALL) $(PYINSTALL_OPTS) $(BUILD)/$(PYDIST)
	@echo "\033[1;32m$(PROJECT) user libraries successfully installed\033[0m"
# @install -v -m 755 $(BUILD_LIB)/$(PYMOD_SHARED_LIB) $(shell $(PYTHON) -m site --user-site)
# @echo "$(PROJECT) user libraries successfully installed"

uninstall:
	@echo "Removing headers and shared/static libraries..."
	@sudo rm -rf $(INSTALL_INCLUDE)
	@sudo rm -f $(INSTALL_LIB)/$(SHARED_LIB) $(INSTALL_LIB)/$(STATIC_LIB)
	@echo "Removing python extension module from user site packages..."
	@$(PYUNINSTALL) $(PYUNINSTALL_OPTS) $(PYMOD)
	@echo "\033[1;32m$(PROJECT) user libraries successfully uninstalled\033[0m"
# @rm -f $(shell $(PYTHON) -m site --user-site)/$(PYMOD_SHARED_LIB)
$(PYMOD): $(BUILD)/$(PYDIST)

shared: $(BUILD_LIB)/$(SHARED_LIB)

static: $(BUILD_LIB)/$(STATIC_LIB)

clean:
	@rm -rf $(BUILD)

# Python distribution

$(BUILD)/$(PYDIST): $(PYMOD_SRC) $(LIB_SRC) | $(BUILD)
	@$(PYMOD_BUILDCMD) $(PYMOD_BUILDOPTS)
	@rm -rf $(PYMOD).egg-info

# Libraries

# $(BUILD_LIB)/$(PYMOD_SHARED_LIB): $(PYMOD_SRC) $(STATIC_OBJS) | $(BUILD_LIB)
# 	@$(PYMOD_BUILDCMD) -I$(INCLUDE) -b$(BUILD_LIB) $(patsubst %,-O%,$(STATIC_OBJS))

$(BUILD_LIB)/$(SHARED_LIB): $(SHARED_OBJS) | $(BUILD_LIB)
	@$(CC) $(CFLAGS) -std=$(STD) -I$(INCLUDE) -shared -o $@ $^

$(BUILD_LIB)/$(STATIC_LIB): $(STATIC_OBJS) | $(BUILD_LIB)
	@$(AR) $(ARFLAGS) $@ $^

# Object files

$(BUILD_SHARED)/%.o: $(SRC)/%.c | $(BUILD_SHARED)
	@$(CC) $(CFLAGS) -std=$(STD) -I$(INCLUDE) -fPIC -c -o $@ $<

$(BUILD_STATIC)/%.o: $(SRC)/%.c | $(BUILD_STATIC)
	@$(CC) $(CFLAGS) -std=$(STD) -I$(INCLUDE) -c -o $@ $<

# Build directories

$(BUILD):
	@mkdir -p $@

$(BUILD_LIB):
	@mkdir -p $@

$(BUILD_SHARED):
	@mkdir -p $@

$(BUILD_STATIC):
	@mkdir -p $@

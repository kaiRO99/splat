##
# splat
#
# @file
# @version 0.1


# Run adapter: lldb-dap :program "bin/md_to_org" :args ["tests/test.md" "tests/test.org"] :compile "make"
# Compier and Flags
CC :=gcc
CFLAGS := -g -O0 -Wall -Wextra -std=c11
CFLAGS += -I./include -I./include/utils -I./tests -I./tests/unity -I./tests/utils -I./src/utils
LIBS := -lwebp -ljpeg -lpng
# add -fsanitize=address for memory error detection
#LDFLAGS := -fsanitize=address
#add -DHAVE_GETOPT_LONG if needed

# Directories
SRC_DIR := src
BIN_DIR := bin
BUILD_DIR:= $(BIN_DIR)/build
TEST_DIR := tests
UNITY_DIR := $(TEST_DIR)/unity
# TEST_HELPERS_DIR := $(TEST_DIR)/utils

# Main program
TARGET:= $(BIN_DIR)/splat
SRCS := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/utils/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

#Testing
UNITY_SRC :=$(UNITY_DIR)/unity.c
TEST_UTILS_SRC :=$(TEST_DIR)/test_utils.c
# TEST_LINE_SRC :=$(TEST_DIR)/test_line.c
# TEST_CLI_SRC :=$(TEST_DIR)/test_cli.c
# TEST_HELPERS_SRC := $(wildcard $(TEST_HELPERS_DIR)/*.c)

# TEST executables (separate binaries for each test suite)
# TEST_FILE_BIN :=$(BIN_DIR)/test_file
TEST_UTILS_BIN:=$(BIN_DIR)/test_utils
TEST_HELP_BIN:=$(Bin_DIR)/test_help
# TEST_LINE_BIN:=$(BIN_DIR)/test_line
# TEST_CLI_BIN:=$(BIN_DIR)/test_cli

#Filter out main.o
TEST_OBJS:= $(filter-out $(BUILD_DIR)/main.o,$(OBJS))

# Default target
.PHONY: all
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)
# add -fsanitize=address

# Compile step
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)/utils
	$(CC) $(CFLAGS) -c $< -o $@

# build test executables
# $(TEST_FILE_BIN): $(TEST_FILE_SRC) $(UNITY_SRC) $(TEST_OBJS) $(TEST_HELPERS_SRC)
# 	@mkdir -p $(BIN_DIR)
# 	$(CC) $(CFLAGS) -o $@ $^

$(TEST_UTILS_BIN): $(TEST_UTILS_SRC) $(UNITY_SRC) $(TEST_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# $(TEST_LINE_BIN): $(TEST_LINE_SRC) $(UNITY_SRC) $(TEST_OBJS) $(TEST_HELPERS_SRC)
# 	@mkdir -p $(BIN_DIR)
# 	$(CC) $(CFLAGS) -o $@ $^

# $(TEST_CLI_BIN): $(TEST_CLI_SRC) $(UNITY_SRC) $(TEST_OBJS) $(TEST_HELPERS_SRC)
# 	@mkdir -p $(BIN_DIR)
# 	$(CC) $(CFLAGS) -o $@ $^

# Run all tests
.PHONY: test
test: clean-test $(TEST_FILE_BIN) $(TEST_UTILS_BIN) $(TEST_LINE_BIN) $(TEST_CLI_BIN)
	@echo ""
	@echo "Running Utility Function Tests..."
	@echo "========================================="
	-@./$(TEST_UTILS_BIN)
	@$(MAKE) clean-test
	@echo ""
	@echo "Running Help Flag Tests..."
	@echo "========================================="
	@chmod +x tests/test_help.sh
	@./tests/test_help.sh
# 	@echo ""
# 	@echo "Running File Conversion Tests..."
# 	@echo "========================================="
# 	-@./$(TEST_FILE_BIN)
# 	@$(MAKE) clean-test
# 	@echo ""
# 	@echo "Running Line Conversion Tests..."
# 	@echo "========================================="
# 	-@./$(TEST_LINE_BIN)
# 	@$(MAKE) clean-test
# 	@echo ""
# 	@echo "Running Command Line Tests..."
# 	@echo "========================================="
# 	-@./$(TEST_CLI_BIN)
# 	@$(MAKE) clean-test
# 	@echo ""
# 	@echo "All tests passed!"

# Run only file tests
# .PHONY: test-file
# test-file: clean-test $(TEST_FILE_BIN)
# 	@echo ""
# 	@echo "========================================="
# 	@echo "Running file conversion tests..."
# 	@echo "========================================="
# 	@./$(TEST_FILE_BIN)
# 	@$(MAKE) clean-test

# Run only utils tests
.PHONY: test-utils
test-utils: $(TEST_UTILS_BIN)
	@echo ""
	@echo "========================================="
	@echo "Running utils conversion tests..."
	@echo "========================================="
	@./$(TEST_UTILS_BIN)

# Run only help flag test
.PHONY: test-help
test-help:
	@echo ""
	@echo "========================================="
	@echo "Running help flag tests..."
	@echo "========================================="
	@chmod +x tests/test_help.sh
	@./tests/test_help.sh

# Run only quality flag test
.PHONY: test-qual
test-qual:
	@echo ""
	@echo "========================================="
	@echo "Running qual flag tests..."
	@echo "========================================="
	@chmod +x tests/test_quality.sh
	@mkdir -p ./tests/fixtures/outputs
	@./tests/test_quality.sh
	@$(MAKE) clean-test

.PHONY: test-out
test-out:
	@echo ""
	@echo "========================================="
	@echo "Running qual flag tests..."
	@echo "========================================="
	@chmod +x tests/test_out.sh
	@mkdir -p ./tests/fixtures/outputs
	@./tests/test_out.sh
	@$(MAKE) clean-test

.PHONY: test-force
test-force:
	@echo ""
	@echo "========================================="
	@echo "Running force flag tests..."
	@echo "========================================="
	@chmod +x tests/test_force.sh
	@mkdir -p ./tests/fixtures/outputs
	@./tests/test_force.sh
	@$(MAKE) clean-test

.PHONY: test-recursive
test-recursive:
	@echo ""
	@echo "========================================="
	@echo "Running recursive flag tests..."
	@echo "========================================="
	@chmod +x tests/test_recursive.sh
	@mkdir -p ./tests/fixtures/outputs
	@./tests/test_recursive.sh
	@$(MAKE) clean-test

.PHONY: test-dry
test-dry:
	@echo ""
	@echo "========================================="
	@echo "Running dry-run flag tests..."
	@echo "========================================="
	@chmod +x tests/test_dry.sh
	@./tests/test_dry.sh
	@$(MAKE) clean-test
# # Run only line tests
# .PHONY: test-line
# test-line: $(TEST_LINE_BIN)
# 	@echo ""
# 	@echo "========================================="
# 	@echo "Running line conversion tests..."
# 	@echo "========================================="
# 	@./$(TEST_LINE_BIN)

# Run only command line tests
# .PHONY: test-cli
# test-cli: clean-test $(TEST_CLI_BIN)
# 	@echo ""
# 	@echo "========================================="
# 	@echo "Running command line tests..."
# 	@echo "========================================="
# 	@./$(TEST_CLI_BIN) || ($(MAKE) clean-test && exit 1)
# 	@$(MAKE) clean-test

# Valgrind mem leak check on tests
# .PHONY: memcheck
# memcheck: $(TEST_UTILS_BIN) $(TEST_FILE_BIN) $(TEST_LINE_BIN) $(TEST_CLI_BIN)
# 	@echo ""
# 	@echo "========================================="
# 	@echo "Checking test_utils for memory leaks..."
# 	valgrind --leak-check=full --show-leak-kinds=all ./$(TEST_UTILS_BIN)
# 	@echo ""
# 	@echo "========================================="
# 	@echo "Checking test_file for memory leaks..."
# 	valgrind --leak-check=full --show-leak-kinds=all ./$(TEST_FILE_BIN)
# 	@echo ""
# 	@echo "========================================="
# 	@echo "Checking test_line for memory leaks..."
# 	valgrind --leak-check=full --show-leak-kinds=all ./$(TEST_LINE_BIN)
# 	@echo ""
# 	@echo "========================================="
# 	@echo "Checking test_cli for memory leaks..."
# 	valgrind --leak-check=full --show-leak-kinds=all ./$(TEST_CLI_BIN)

# Clean
#
# rm -rf $(BUILD_DIR) $(TARGET) $(TEST_FILE_BIN) $(TEST_UTILS_BIN) $(TEST_LINE_BIN)
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TEST_UTILS_BIN) $(TEST_HELP_BIN)

# Clean Test
.PHONY: clean-test
clean-test:
	@echo "Cleaning up test files"
	@rm -rf tests/fixtures/outputs
	@rm -f tests/fixtures/*.webp

# Convenience targets
.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: debug
debug: $(TARGET)
	lldb ./$(TARGET)

# Help target
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  make              - Build the main program"
	@echo "  make test         - Build and run all tests"
	@echo "  make test-utils   - Run only utility function tests"
	@echo "  make test-help    - Run only help flag test"
	# @echo "  make test-file    - Run only file conversion tests"
	# @echo "  make test-line    - Run only line conversion tests"
	# @echo "  make test-cli     - Run only command line tests"
	# @echo "  make memcheck     - Run tests with valgrind (check for leaks)"
	# @echo "  make run          - Build and run the program"
	# @echo "  make debug        - Build and run with lldb debugger"
	# @echo "  make clean        - Remove all build artifacts"
	# @echo "  make help         - Show this help message"

# .PHONY: all clean run debug test test-utils test-file test-line test-cli memcheck help
.PHONY: all clean run debug test test-utils
#
# end

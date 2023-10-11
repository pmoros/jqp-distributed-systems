# Makefile

CC = gcc
CFLAGS = -Wall

# Source files in the src directory
SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Source files in the utils directory
UTILS_DIR = utils
UTILS_SRCS = $(wildcard $(UTILS_DIR)/*.c)

# Object files directory
BUILD_DIR = build

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS)) $(patsubst $(UTILS_DIR)/%.c,$(BUILD_DIR)/%.o,$(UTILS_SRCS))

# Executable name and directory
EXEC_DIR = bin
EXEC = $(EXEC_DIR)/jgs

# Include path for header files
INC_DIR = utils

$(EXEC): $(OBJS)
	@mkdir -p $(EXEC_DIR)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) -I$(INC_DIR)

# Rule to compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

$(BUILD_DIR)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

clean:
	rm -rf $(EXEC_DIR) $(BUILD_DIR)

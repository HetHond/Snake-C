TARGET := snake

CC := clang
CFLAGS =
LDFLAGS := -lSDL2 # Not sure if this is supposed to be put here but it works

SRC_DIR := src
SOURCES := $(wildcard $(SRC_DIR)/*.c)

BUILD_DIR := build
OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(TARGET)

$(BUILD_DIR):
	@mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	@rm -rf $(OBJECTS) $(BUILD_DIR) $(TARGET)
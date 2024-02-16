TARGET := snake

CC := clang
CXX := clang++
CFLAGS :=
CXXFLAGS :=

LINKER := $(CXX)
LDFLAGS := -lSDL2

SRC_DIR := src
SOURCES_C := $(wildcard $(SRC_DIR)/*.c)
SOURCES_CPP := $(wildcard $(SRC_DIR)/*.cpp)

BUILD_DIR := build

OBJECTS_C := $(SOURCES_C:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJECTS_CPP := $(SOURCES_CPP:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
OBJECTS := $(OBJECTS_C) $(OBJECTS_CPP)

all: $(TARGET)

$(BUILD_DIR):
	@mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(TARGET): $(OBJECTS)
	$(LINKER) $^ $(LDFLAGS) -o $(TARGET)

clean:
	@rm -rf $(OBJECTS) $(BUILD_DIR) $(TARGET)
CPP_FLAGS = -std=c++11 -Wall -Wextra -Werror -g
SOURCES = $(wildcard src/*.cpp)
TARGET = decide
OBJECTS = $(addprefix build/,$(notdir $(SOURCES:.cpp=.o)))
OPT = -O0
BUILD_DIR = build

$(info $(SOURCES))

ifeq ($(CXX), clang++)
	CPPCC = clang++
else ifeq ($(CXX), g++)
	CPPCC = g++
else
	@echo "Compiler not supported. Using g++"
	CPPCC = g++
endif


all: $(BUILD_DIR)/$(TARGET)


$(BUILD_DIR)/%.o: src/%.cpp Makefile | $(BUILD_DIR)
	$(CPPCC) $(CPP_FLAGS) $(OPT) -c $< -o $@

$(BUILD_DIR)/$(TARGET): $(OBJECTS) Makefile
	$(CPPCC) $(CPP_FLAGS) $(OPT) $(OBJECTS) -o $@

$(BUILD_DIR):
	@mkdir -p $@


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
CPP_FLAGS = -std=c++11 -Wall -Wextra -Werror -g
SOURCES = $(wildcard src/*.cpp)
TARGET = decide
OBJECTS = $(SOURCES:.cpp=.o)
OPT = -O0


$(info $(SOURCES))

ifeq ($(CXX), clang++)
	CPPCC = clang++
else ifeq ($(CXX), g++)
	CPPCC = g++
else
	@echo "Compiler not supported. Using g++"
	CPPCC = g++
endif


# all: 
# 	@mkdir -p build
# 	$(CPPCC) $(CPP_FLAGS) $(SOURCES) -o build/
all: build/$(TARGET)

build/%.o: src/%.cpp
	@mkdir -p build
	$(CPPCC) $(CPP_FLAGS) $(OPT) -c $< -o $@

build/$(TARGET): $(OBJECTS)
	@mkdir -p build
	$(CPPCC) $(CPP_FLAGS) $(OPT) $(OBJECTS) -o $@

.PHONY: clean
clean:
	rm -rf build

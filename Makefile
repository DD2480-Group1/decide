CPP_FLAGS = -std=c++11 -Wall -Wextra -Werror -g
SOURCES = $(wildcard src/*.cpp)
TARGET = decide

$(info $(SOURCES))

ifeq ($(CXX), clang++)
	CPPCC = clang++
else ifeq ($(CXX), g++)
	CPPCC = g++
else
	@echo "Compiler not supported. Using g++"
	CPPCC = g++
endif


all: 
	@mkdir -p build
	$(CPPCC) $(CPP_FLAGS) $(SOURCES) -o build/decide.exe

clean:
	rm -rf build/

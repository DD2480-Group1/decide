CPP_FLAGS = -std=c++11 -Wall -Wextra -Werror -pedantic -g
CPPCC = g++
SOURCES = $(wildcard src/*.cpp)
TARGET = decide

$(info $(SOURCES))


all: 
	@mkdir -p build
	$(CPPCC) $(CPP_FLAGS) $(SOURCES) -o build/decide.exe

clean:
	rm -rf build/

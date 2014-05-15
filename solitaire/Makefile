#-include Makefile.deps

# define the C compiler to use
CC = clang++

# define any compile-time flags
CFLAGS = -I./src -Wall -std=c++11 -stdlib=libc++

# define the C source files
SRCS := main.cpp $(wildcard src/*.cpp)
OBJS := $(SRCS:src=build:.cpp=.o)
MAIN = solitaire


.PHONY: clean

all: Makefile.deps $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o build/$(MAIN) $(OBJS)

%.o: %.cpp *.h
	$(CC) $(CFLAGS) -c $< -o build/$@

clean:
	$(RM) build/*

Makefile.deps: $(SRCS)
	$(CC) $(CFLAGS) -MM $^ > Makefile.deps

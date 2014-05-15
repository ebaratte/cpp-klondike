#-include Makefile.deps

# define the C compiler to use
CC = clang++

# define any compile-time flags
CFLAGS = -Wall -std=c++11 -stdlib=libc++

# define the C source files
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
MAIN = solitaire



.PHONY: clean

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

%.o: %.cpp *.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o *~ $(MAIN)

Makefile.deps: $(SRCS)
	$(CC) -MM $^ > Makefile.deps

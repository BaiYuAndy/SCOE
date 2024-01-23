# Specify the compiler
CC = g++

# Specify compilation flags
CFLAGS = -I ../include -L ../lib -l SDL2-2.0.0

#speator the compile line
CLIB = -L ../lib -l SDL2-2.0.0
CINC = -I ../include

# Specify the target executable
TARGET = play

# Define the source files
SRCS = main.cpp

# Define object files from source files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: 
	@ $(CC) $(SRCS) -c $< -o $(OBJS) $(CINC)
	@ $(CC) $(OBJS) -o $(TARGET) $(CFLAGS)

# Clean up the compiled files
clean:
	@ rm -f $(OBJS) $(TARGET)

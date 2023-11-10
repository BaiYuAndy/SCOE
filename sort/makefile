# Specify the compiler
CC = g++

# Specify compilation flags
CFLAGS = -Wall -g

# Define the source files
SRCS = test.cpp

# Specify the target executable
TARGET = $(patsubst %.cpp, %, $(SRCS));

# Define object files from source files
OBJS = $(SRCS:.cpp=.o)

# Default target
all:
	@ $(CC) $(CFLAGS) $(SRCS) -c $< -o $(OBJS)
	@ $(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

#Clean up the compiled files
clean:
	@ rm -f $(OBJS) $(TARGET)

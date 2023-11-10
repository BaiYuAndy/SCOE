# Specify the compiler
CC = g++

# Specify compilation flags
CFLAGS = -Wall -g

# Define the source files
SRCS = djk.cpp

# Specify the target executable
TARGET = $(patsubst %.cpp, %, $(SRCS));

# Define object files from source files
OBJS = $(SRCS:.cpp=.o)

MESSAGE := "this is compile djkstra"

# Default target
all:
	#@ $(CC) $(CFLAGS) $(SRCS) -c $< -o $(OBJS)
	#@ echo $(MESSAGE)
	#@ $(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
	@ $(CC) $(SRCS) -o $(TARGET)

#Clean up the compiled files
clean:
	@ rm -f $(OBJS) $(TARGET)

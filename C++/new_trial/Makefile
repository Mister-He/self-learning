# Define the compiler
CXX = g++

# Define the target executable
TARGET = main

# Define the source files
SRCS = main.cpp

# Define the object files
OBJS = $(SRCS:.cpp=.o)

# Define the build rule for the target
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

# Define the build rule for the object files
%.o: %.cpp
	$(CXX) -c $< -o $@

# Define the clean rule
clean:
	rm -f $(TARGET) $(OBJS)
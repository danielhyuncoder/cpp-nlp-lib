# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17

# Target executable name
TARGET = app

# Source files
SRCS = main.cpp src/NLP.cpp

# Object files (automatically replace .cpp with .o)
OBJS = $(SRCS:.cpp=.o)

# Default rule
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)

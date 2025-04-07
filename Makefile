CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20
LDFLAGS = -lws2_32
SRC = main.o

# Default target
all: main

# Compile the webserver
main: main.o Server.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Clean up compiled files
clean:
	del $(TARGET)

# Run the server
run: $(TARGET)
	.\$(TARGET)

# Phony targets (not actual files)
.PHONY: all clean run

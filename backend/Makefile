CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
TARGET := erp_backend_demo

SOURCES := $(shell find src -name '*.cpp')
OBJECTS := $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: all
	./$(TARGET)

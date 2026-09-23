CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic

TARGET := spn
SOURCES := logger.cpp rounds.cpp spn.cpp

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

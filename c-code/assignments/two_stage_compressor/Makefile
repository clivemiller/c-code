CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic
SRC := src/main.cpp
TARGET := twostage

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

.PHONY: all clean

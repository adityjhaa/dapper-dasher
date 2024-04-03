.DEFAULT_GOAL := all

CXX := g++
CCBUILDFLAGS := -o

RAYLIB_FLAG := -lraylib

TARGET := game
SRC_PATH := .

ifeq ($(OS),Windows_NT)
	TARGET := $(addsuffix .exe,$(TARGET))
endif

SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.cpp)))

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRC) 
	$(CXX) $(CCBUILDFLAGS) $@ $(SRC) $(RAYLIB_FLAG)

.PHONY: run
run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

CC = g++

INCL_DIR := -I../incl
SRC_DIR := ../src
OBJ_DIR := ../obj
BIN_DIR := ../bin

EXE := $(BIN_DIR)/frequencyDetector
SRC := $(wildcard $(SRC_DIR)/*.cpp main.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CC := g++ -std=c++11
CPPFLAGS := -O3 -MMD -MP -Wall -g -fPIC -DHAVE_GETTIMEOFDAY -D__MACOSX_CORE__ -D__OS_MACOSX__ -D__LITTLE_ENDIAN__
LDLIBS := -lpthread -framework CoreAudio -framework CoreFoundation -framework CoreMIDI /usr/local/lib/libkissfft-float.dylib

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(INCL_DIR) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(INCL_DIR) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)
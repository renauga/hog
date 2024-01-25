CC = g++
CPPFLAGS = -Iinclude# general flags related to c++
CXXFLAGS = -c # compilation and assembly flags
LDFLAGS =   # linker flags
# MODE_FLAG = -g -pg -DDEBUG
MODE_FLAG = -g -O3
.DEFAULT_GOAL := all
INCLUDE_DIR = include
BIN_DIR = bin
SRC_DIR = src
TEST_DIR = tests
TARGET = $(BIN_DIR)/testHOG
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(SRC_FILES))

all : ssp run

sk : $(OBJECTS) $(TEST_DIR)/testHOG.cpp
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(MODE_FLAG) $^ -DSK -o $(TARGET)

ssp : $(OBJECTS) $(TEST_DIR)/testHOG.cpp
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(MODE_FLAG) $^ -DSSP -o $(TARGET)

ec : $(OBJECTS) $(TEST_DIR)/testHOG.cpp
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(MODE_FLAG) $^ -DEC -o $(TARGET)

bcer : $(OBJECTS) $(TEST_DIR)/testHOG.cpp
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(MODE_FLAG) $^ -DBCER -o $(TARGET)

aho : $(OBJECTS) $(TEST_DIR)/testAho-Cora.cpp
	$(CC) $(CPPFLAGS) $(LDFLAGS) $(MODE_FLAG) $^ -o $(BIN_DIR)/testAho-Cora

$(BIN_DIR)/%.o : $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/%.h
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(MODE_FLAG) $< -o $@

run : $(TARGET)
	./$(TARGET)

clean :
	rm -rf $(BIN_DIR)/*

.PHONY : clean sk ssp ec bcer aho run
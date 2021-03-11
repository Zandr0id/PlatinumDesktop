OUTPUT_FILE = desktop.bin

SRC_FILES = $(wildcard *.cpp)

CPP = clang++

BUILD_FLAGS = -std=c++17 -g

LINK_FLAGS = -lSDL2

build : $(OUTPUT_FILE)

$(OUTPUT_FILE) : $(SRC_FILES)
	$(CPP) $(SRC_FILES) -o $(OUTPUT_FILE) $(BUILD_FLAGS) $(LINK_FLAGS)

clean :
	rm $(OUTPUT_FILE)

run :
	./$(OUTPUT_FILE)

OUTPUT_FILE = desktop

SRC_FILES = $(wildcard *.cpp)

CPP = clang++

LINK_FLAGS = -lSDL2 -std=c++17 -g

build : $(OUTPUT_FILE)

$(OUTPUT_FILE) : $(SRC_FILES)
	$(CPP) $(SRC_FILES) -o $(OUTPUT_FILE) $(LINK_FLAGS)

clean :
	rm $(OUTPUT_FILE)

run :
	./$(OUTPUT_FILE)

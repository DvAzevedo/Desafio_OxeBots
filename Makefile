# Define the compiler
CC := g++


# Define the source files
SOURCE_FILES := $(wildcard src/*.cpp)
$(info Source files: $(SOURCE_FILES))

# Define the object file names
OBJECTS := $(SOURCE_FILES:.cpp=.o)
$(info Object files: $(OBJECTS))

# Define the executable name
EXEC := executable.out
$(info Executable: $(EXEC))

# Debug flags
DEBUG_FLAGS := -g -O0 -Wall -Wextra -Wpedantic -Werror

# Release flags
RELEASE_FLAGS := -O3

# Default flags
CXXFLAGS := $(RELEASE_FLAGS)

ifeq ($(OS),Windows_NT)
	SDL2_FLAGS := -IC:/Users/davia/Downloads/sdl/SDL2-2.30.2/i686-w64-mingw32/include -LC:/Users/davia/Downloads/sdl/SDL2-2.30.2/i686-w64-mingw32/lib -lSDL2
	CLEAN_CMD := del /f /q $(subst /,\,$(OBJECTS)) $(EXEC)
else
	SDL2_FLAGS := $(shell pkg-config --libs sdl2)
	CLEAN_CMD := rm -f $(OBJECTS) $(EXEC)
endif
$(info SDL2 flags: $(SDL2_FLAGS))

all: $(EXEC)
	$(info Compilation successful!)

debug: CXXFLAGS := $(DEBUG_FLAGS)
debug: all
	$(info Compiled for debugging...)

release: CXXFLAGS := $(RELEASE_FLAGS)
release: all
	$(info Compiled for release...)


# Compile the source code into object files
%.o: %.cpp
	$(info Compiling $<...)
	$(CC) -c $< -o $@ $(CXXFLAGS) $(SDL2_FLAGS)

# Link the object files with SDL2 library to create the executable
$(EXEC): $(OBJECTS)
	$(info Linking the object files...)
	$(CC) $(OBJECTS) -o $(EXEC) $(SDL2_FLAGS)

# Clean the project (removes object files and executable)
clean:
	$(info Cleaning the project...)
	$(CLEAN_CMD)

# Run the program
run:
	$(info Running the program...)
	./$(EXEC)

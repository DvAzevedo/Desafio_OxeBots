# Define the compiler
CC := g++

# Define the source files
SOURCE_FILES := $(wildcard src/*.cpp)
$(info Source files: $(SOURCE_FILES))
JOYSTICK_FILES := $(wildcard src/Joy/Joy.cpp)

# Define the object file names
OBJECTS := $(SOURCE_FILES:.cpp=.o)
$(info Object files: $(OBJECTS))

# Define the executable name
SIMULATION := sim.exe
JOYSTICK := joystick.exe
$(info Executables: $(SIMULATION) $(JOYSTICK))

# Define the protobuf files
PROTO_FILES := $(wildcard proto/*.proto)
PROTO_CPP_FILES := $(PROTO_FILES:.proto=.pb.cc)
PROTO_H_FILES := $(PROTO_FILES:.proto=.pb.h)
$(info Proto files: $(PROTO_FILES))

# Specify the directory containing the generated header files
PROTO_INCLUDE_DIR := .
CXXFLAGS := -I$(PROTO_INCLUDE_DIR)

# Add the proto files to the source files and objects
SOURCE_FILES += $(PROTO_CPP_FILES)
OBJECTS += $(PROTO_CPP_FILES:.cc=.o)

# Debug and release flags
DEBUG_FLAGS := ${CXXFLAGS} -g -O0 -Wall -Wextra -Wpedantic -Werror
RELEASE_FLAGS := ${CXXFLAGS} -O3

# Determine platform-specific settings
ifeq ($(OS),Windows_NT)
	LIBS_FLAGS := -LC:/Users/davia/Downloads/sdl/SDL2-2.30.2/i686-w64-mingw32/lib -lSDL2
	CLEAN_CMD := del /f /q $(subst /,\,$(OBJECTS) $(PROTO_CPP_FILES) $(PROTO_H_FILES)) $(SIMULATION) $(JOYSTICK)
else
	LIBS_FLAGS := $(shell pkg-config --libs sdl2) $(shell pkg-config --libs protobuf) $(shell pkg-config --libs ncurses)
	CLEAN_CMD := rm -f $(OBJECTS) $(SIMULATION) $(PROTO_CPP_FILES) $(PROTO_H_FILES) $(JOYSTICK)
endif
$(info LIB flags: $(LIBS_FLAGS))

# Default target
all: $(PROTO_CPP_FILES) $(SIMULATION) $(JOYSTICK)
	$(info Compilation successful!)

# Debug target
debug: CXXFLAGS := $(DEBUG_FLAGS)
debug: all
	$(info Compiled for debugging...)

# Release target
release: CXXFLAGS := $(RELEASE_FLAGS)
release: all
	$(info Compiled for release...)

# Rule to compile source files
%.o: %.cpp
	$(info Compiling $<...)
	$(CC) -c $< -o $@ $(CXXFLAGS) $(LIBS_FLAGS)

# Rule to link object files and create the executable
$(SIMULATION): $(OBJECTS)
	$(info Linking the object files...)
	$(CC) $(OBJECTS) -o $(SIMULATION) $(LIBS_FLAGS)

# Rule to compile protobuf files
$(PROTO_CPP_FILES) $(PROTO_H_FILES): $(PROTO_FILES)
	$(info Compiling Protobuf files...)
	protoc --cpp_out=. $(PROTO_FILES)

$(JOYSTICK): $(JOYSTICK_FILES)
	$(info Compiling Joystick files...)
	$(CC) $(JOYSTICK_FILES) $(PROTO_CPP_FILES) -o $(JOYSTICK) $(CXXFLAGS) $(LIBS_FLAGS)

# Clean rule
clean:
	$(info Cleaning the project...)
	$(CLEAN_CMD)

# Run rule
run:
	$(info Running the program...)
	./$(SIMULATION)

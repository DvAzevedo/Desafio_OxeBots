# Define o compilador
CC := g++

# Define os arquivos fonte
SOURCE_FILES := $(wildcard src/*.cpp)
$(info Source files: $(SOURCE_FILES))

# Define os nomes dos arquivos de objeto
OBJECTS := $(SOURCE_FILES:.cpp=.o)
$(info Object files: $(OBJECTS))

# Define o nome do executável
EXEC := executable.out
$(info Executable: $(EXEC))

# Flags de depuração
DEBUG_FLAGS := -g -O0 -Wall -Wextra -Wpedantic -Werror

# Flags de lançamento
RELEASE_FLAGS := -O3

# Flags padrão
CXXFLAGS := $(RELEASE_FLAGS) $(SDL_INCLUDE_FLAGS)

ifeq ($(OS),Windows_NT)
    # Se estiver no Windows, utilize a variável de ambiente SDL2_PATH
    LIBS_FLAGS := -LC:/Users/davia/Downloads/sdl/SDL2-2.30.2/i686-w64-mingw32/lib -lSDL2
    SDL_INCLUDE_FLAGS := -IC:/Users/davia/Downloads/sdl/SDL2-2.30.2/i686-w64-mingw32/include
    CLEAN_CMD := del /f /q $(subst /,\,$(OBJECTS) $(PROTO_CPP_FILES) $(PROTO_H_FILES)) $(SIMULATION) $(JOYSTICK)
else
    # Se não estiver no Windows, use pkg-config para obter as flags das bibliotecas
    LIBS_FLAGS := $(shell pkg-config --libs sdl2) $(shell pkg-config --libs protobuf) $(shell pkg-config --libs ncurses)
    SDL_INCLUDE_FLAGS := $(shell pkg-config --cflags sdl2)
    CLEAN_CMD := rm -f $(OBJECTS) $(SIMULATION) $(PROTO_CPP_FILES) $(PROTO_H_FILES) $(JOYSTICK)
endif
# Compilação de cada arquivo fonte
src/%.o: src/%.cpp
	@echo "Compiling $<..."
	@$(CXX) -c $< -o $@ $(CXXFLAGS) $(SDL_INCLUDE_FLAGS)

all: $(EXEC)
	$(info Compilation successful!)

debug: CXXFLAGS := $(DEBUG_FLAGS)
debug: all
	$(info Compiled for debugging...)

release: CXXFLAGS := $(RELEASE_FLAGS)
release: all
	$(info Compiled for release...)

# Link os arquivos de objeto com a biblioteca SDL2 para criar o executável
$(EXEC): $(OBJECTS)
	$(info Linking the object files...)
	$(CC) $(OBJECTS) -o $(EXEC) $(LIBS_FLAGS)

# Limpa o projeto (remove arquivos de objeto e executável)
clean:
	$(info Cleaning the project...)
	$(CLEAN_CMD)

# Executa o programa
run:
	$(info Running the program...)
	./$(EXEC)


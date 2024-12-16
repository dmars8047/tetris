OBJS = ./src/*.cpp

CC = g++

MCC = clang++

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

BIN = ./bin/

LINUX_APP_NAME = tetris

linux : $(OBJS)
	$(CC) -std=c++17 $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -g -o $(BIN)$(LINUX_APP_NAME)

MAC_INCLUDE_PATHS = -I/opt/homebrew/include/SDL2/
MAC_LIBRARY_PATHS = -L/opt/homebrew/lib
MAC_APP_NAME = tetris

mac : $(OBJS)
	$(MCC) -std=c++17 $(OBJS) $(MAC_INCLUDE_PATHS) $(MAC_LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -g -o $(BIN)$(MAC_APP_NAME)
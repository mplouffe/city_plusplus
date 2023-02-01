# OBJS - specifies which files to compile as part of the project
OBJS = sim.cpp

# CC - specifies which compiler
CC = g++

# INCLUDE_PATHS - specifies additional include paths
INCLUDE_PATHS = -IE:\dev_lib\SDL2-2.26.2\i686-w64-mingw32\include\SDL2 -IE:\dev_lib\SDL2_image-2.6.2\i686-w64-mingw32\include\SDL2 -IE:\dev_lib\SDL2_ttf-2.20.1\i686-w64-mingw32\include\SDL2

# LIBRARY_PATHS - specifies additional library paths
LIBRARY_PATHS = -LE:\dev_lib\SDL2-2.26.2\i686-w64-mingw32\lib -LE:\dev_lib\SDL2_image-2.6.2\i686-w64-mingw32\lib -LE:\dev_lib\SDL2_ttf-2.20.1\i686-w64-mingw32\lib

# COMPILER_FLAGS - specifies the ad ditional compiltion options
# -w = supresses all warnings
# -Wl,-subsystem,windows = gets rid of console window
COMPILER_FLAGS = -w -Wl,-subsystem,windows

# LINKER_FLAGS - specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

# OBJ_NAME - specifies the name of the exe
OBJ_NAME = citypp_sim

# EXE_NAME - name of the output exe
EXE_NAME = citypp_sim

# PROG_PATH - path of folder for output of executable
PROG_PATH = ../bin/

# This is the target that compiles the executable
all: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	mv $(EXE_NAME) $(PROG_PATH)
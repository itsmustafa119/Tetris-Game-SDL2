# Compiler and target settings
TARGET     = tetris.exe
CC         = gcc

# Include and library directories for SDL2
INCLUDE_DIR = C:/mingw64/include
LIB_DIR     = C:/mingw64/lib

# Compilation and linking flags
CFLAGS  = -I$(INCLUDE_DIR) -Wall -O2          # include SDL2 headers, enable warnings, optimization
LDFLAGS = -L$(LIB_DIR)                        # link directory for SDL2 libraries
LIBS    = -lmingw32 -lSDL2main -lSDL2 \
          -lSDL2_ttf -lSDL2_image -lSDL2_mixer  # SDL2 and addon libraries

# Source and object files
SOURCES = main.c function.c
OBJECTS = main.o function.o

# Default build target
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(LIBS)

# Compile .c to .o (object files)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJECTS) $(TARGET)

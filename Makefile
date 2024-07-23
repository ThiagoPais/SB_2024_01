SRC_DIR := src
OBJ_DIR := obj

EXE1 := montador
EXE2 := ligador

# Source files for each executable
SRC := $(wildcard $(SRC_DIR)/*.cpp)
SRC1 := $(filter-out $(SRC_DIR)/ligador.cpp, $(SRC))
SRC2 := $(filter-out $(SRC_DIR)/montador.cpp, $(SRC))


# Object files for each executable
OBJ1 := $(SRC1:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
OBJ2 := $(SRC2:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude -MMD -MP
CFLAGS   := -Wall
LDFLAGS  := -Llib
LDLIBS   := -lm
CC       := g++

.PHONY: all clean

all: $(EXE1) $(EXE2)

$(EXE1): $(OBJ1) 
	$(CC) $(LDFLAGS) $(OBJ1) $(LDLIBS) -o $@

$(EXE2): $(OBJ2) 
	$(CC) $(LDFLAGS) $(OBJ2) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(OBJ_DIR)

-include $(OBJ1:.o=.d) $(OBJ2:.o=.d)

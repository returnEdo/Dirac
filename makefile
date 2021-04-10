CC := g++
CFLAGS := $(CFLAGS)
LDFLAGS := -lGL -lGLU -lGLEW -lglfw
BIN_DIR := bin
CPP_SOURCE := $(wildcard *.cpp)
OBJ_DEST  := $(CPP_SOURCE:%.cpp=$(BIN_DIR)/%.o)
 
 
main: $(OBJ_DEST)
	$(CC) $(OBJ_DEST) -o $@ $(LDFLAGS)
 
 
$(OBJ_DEST): $(BIN_DIR)/%.o : %.cpp
	$(CC) -c $< -o $@ $(LDFLAGS)
                 
clean:
	rm $(BIN_DIR)/*.o


MODULE=Graph
CC=g++
C_FLAGS=-Wall -Werror -std=c++0x
OBJ=sampleGraph
INC=../
MAIN_SRC=test/sampleGraph.cpp
SRC=UniqueId.cpp Edge.cpp Vertex.cpp $(MAIN_SRC)
SRC_FULL=$(addprefix $(MODULE)/src/,$(SRC))

all:
	$(CC) $(C_FLAGS) -o $(OBJ) -I$(INC) $(SRC_FULL)

clean:
	rm $(OBJ)

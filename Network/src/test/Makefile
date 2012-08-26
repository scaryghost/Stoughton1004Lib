CPPC=g++
INC=..
LIB=dist/Stoughton1004Lib.a
OBJ=webserver
CFLAGS=-std=c++0x -lpthread

all:
	$(CPPC) -I$(INC) Network/src/test/webserver.cpp $(LIB) -o $(OBJ) $(CFLAGS)

clean:
	rm -rf $(OBJ)

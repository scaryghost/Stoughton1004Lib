CFLAGS=-std=c++0x -Werror -Wall

doc:
	doxygen config/Stoughton1004Lib.doxyfile

clean:
	rm -R $(DIST)

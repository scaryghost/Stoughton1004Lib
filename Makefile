DIST=dist

doc:
	doxygen config/Stoughton1004Lib.doxyfile

clean:
	rm -R $(DIST)

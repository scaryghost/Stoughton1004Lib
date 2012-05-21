include config.mk

CPPC=g++
DIST=dist/
LIB=Stoughton1004Lib.a
MODULE_CONFIG= $(foreach module, $(MODULES), $(module)/src/config.mk)
SRCS:=
INC=../
CPP_FLAGS=-std=c++0x -Werror -Wall -I$(INC)

include $(MODULE_CONFIG)

OBJS= $(patsubst %.cpp, %.o, $(SRCS))

all: $(OBJS)
	@echo $(SRCS)
	if [ ! -e $(DIST) ]; then \
	    mkdir $(DIST); \
	fi
	ar -cvq $(DIST)$(LIB) $(OBJS)

%.o: %.cpp
	$(CPPC) -c $(CPP_FLAGS) $< -o $@

doc:
	doxygen config/Stoughton1004Lib.doxyfile

clean:
	rm -f -R $(DIST) $(OBJS)

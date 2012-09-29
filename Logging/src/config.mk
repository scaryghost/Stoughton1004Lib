M_DIR=Logging
M_SRCS=FileHandler.cpp  Logger.cpp  SocketHandler.cpp
SRCS:= $(SRCS) $(addprefix $(M_DIR)/src/,$(M_SRCS))

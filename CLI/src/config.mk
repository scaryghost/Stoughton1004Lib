M_DIR=CLI
M_SRCS=Arguments.cpp CLIBuilder.cpp Option.cpp
SRCS:= $(SRCS) $(addprefix $(M_DIR)/src/,$(M_SRCS))

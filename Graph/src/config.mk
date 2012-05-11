M_DIR=Graph
M_SRCS=Vertex.cpp Edge.cpp UniqueId.cpp
SRCS:= $(SRCS) $(addprefix $(M_DIR)/src/,$(M_SRCS))

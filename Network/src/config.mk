M_DIR=Network
M_SRCS=DatagramPacket.cpp DatagramSocket.cpp
SRCS:= $(SRCS) $(addprefix $(M_DIR)/src/,$(M_SRCS))
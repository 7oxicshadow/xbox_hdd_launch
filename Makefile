XBE_TITLE = xbox_hdd_launch
GEN_XISO = $(XBE_TITLE).iso
SRCS = $(CURDIR)/main.c
NXDK_DIR = $(CURDIR)/externals/nxdk

include $(NXDK_DIR)/Makefile

MODULE	= main 

EXE			= $(MODULE)

CCFLAGS	+= \
					`pkg-config --cflags jlwuit` \

LDFLAGS	+= \
					`pkg-config --libs jlwuit` \

OBJS 		= \
					main.o \
	   
include ../../Makefile.defs
include ../../Makefile.build


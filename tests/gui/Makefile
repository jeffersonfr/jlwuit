MODULE	= main 

EXE			= $(MODULE)

CCFLAGS	+= \
					`pkg-config --cflags jlwuit` \
					`pkg-config --cflags libxine` \

LDFLAGS	+= \
					`pkg-config --libs jlwuit` \
					`pkg-config --libs libxine` \

OBJS 		= \
					main.o \
	   
include ../../Makefile.defs
include ../../Makefile.build


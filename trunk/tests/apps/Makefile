MODULE	= main 

EXE			= $(MODULE)

CCFLAGS	+= \
					-Isrc/include \
					`pkg-config --cflags jlwuit` \
					`pkg-config --cflags libxine` \

LDFLAGS	+= \
					`pkg-config --libs jlwuit` \
					`pkg-config --libs libxine` \

OBJS 		= \
					calc.o\
					main.o\
					photoslider.o\
					mp3player.o\
					mp4player.o\
	   
include ../../Makefile.defs
include ../../Makefile.build


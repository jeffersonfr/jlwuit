MODULE	= main 

EXE			= $(MODULE)

CCFLAGS	+= \
					-Isrc/include \
					`pkg-config --cflags jlwuit` \

LDFLAGS	+= \
					`pkg-config --libs jlwuit` \

OBJS 		= \
					calc.o\
					main.o\
					photoslider.o\
					mp3player.o\
					mp4player.o\
					screensaver.o\
	   
include ../../Makefile.defs
include ../../Makefile.build


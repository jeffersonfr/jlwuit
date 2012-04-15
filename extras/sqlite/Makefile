MODULE	= sqlite

EXE			= $(MODULE)

CCFLAGS	+= \
					 -Isrc/include \

LDFLAGS	+= \
					 -ldl -lpthread \

OBJS 		= \
					shell.o \
					sqlite3.o \
	   
include ../../Makefile.defs
include ../../Makefile.build


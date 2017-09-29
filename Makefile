#
#  Makefile
#  SudokuSolver
#
#

# C Compile Flags
ifeq ($(LINUX), 1)
CC = gcc
CFLAGS = -std=gnu11
else
CC = clang++
CFLAGS = -I/usr/local/Cellar/glew/2.0.0/include -I/usr/local/include -std=c++11
endif

ifeq ($(LINUX), 1)
ifeq ($(DEBUG), 1)
CFLAGS += -g -D DEBUG -D LINUX
else
CFLAGS += -D LINUX
endif
else
ifeq ($(DEBUG), 1)
CFLAGS += -glldb -D DEBUG 
else
CFLAGS += -O3
endif
endif

# C Linker flags
ifeq ($(LINUX), 1)
LDFLAGS = -lGL -lglut -lm -lrt -lGLU
else
LDFLAGS = -L/usr/local/lib -L/usr/local/Cellar/glew/2.0.0/lib -lglew -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
endif

# Project files
SRCS = src/SudokuSolver.cpp
OBJS = $(SRCS:.c=.o)
MAIN = priv/SudokuSolver

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all:    $(MAIN) 
		@echo SudokuSolver has been compiled

$(MAIN): $(OBJS) 
		$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(LDFLAGS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o: 
		$(CC) $(CFLAGS) -c $<  -o $@

clean: 
		$(RM) src/*.o *~ $(MAIN)

depend: 
		$(SRCS) makedepend $^

# DO NOT DELETE THIS LINE -- make depend needs it
#sample Makefile for using OpenGL of Red Hat Linux 7.x
#CS 420, Tong Yu, Fall 2002

PROG	= shadow
TOP = /apps/opengl/Mesa-7.0.3
CFLAGS	= -w -s -O2 -ansi -DSHM
XLIBS	= -lX11 -lXext -lXmu -lXext -lXmu -lXt -lXi -lSM -lICE 
#-lSDL
LIBS	= -lglut -lGLU -lGL  -lpng
LIBDIR	= -L/usr/X11/lib -L/usr/X11R6/lib -L$(TOP)/lib -L.
UTILDIR = /apps/courses/cs420/others
INCLS	= -I/usr/X11R/include -I/share/mesa/include -I../ -I$(TOP)/include -I$(UTILDIR) -I$(UTILDIR)/canvas -I$(UTILDIR)/../imageio

UTILOBJS = $(UTILDIR)/canvas/rectangle.o $(UTILDIR)/../imageio/imageio.o 
#source codes
DIR=../
SRCS = $(PROG).cpp 
OBJ1 = $(SRCS:.cpp=.o) main.o 
#OBJ1 = $(SRCS:.cpp=.o) scene.o 
#substitute .cpp by .o to obtain object filenames
OBJS =  

#$< evaluates to the target's dependencies, 
#$@ evaluates to the target

$(PROG): $(OBJS)  $(OBJ1)
	g++ -o $@ $(OBJS) $(OBJ1) $(LIBDIR) $(LIBS) $(XLIBS)

$(OBJS): 
	echo $(INCLS)
	gcc -c  $*.c $(INCLS)

$(OBJ1):
	g++ -c $*.cpp $(INCLS)  

run:
	export LD_LIBRARY_PATH=/usr/lib64; ./$(PROG)
clean:
	rm $(OBJ1)

clean1:
	rm ../$(temp)


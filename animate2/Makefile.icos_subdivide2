#sample Makefile for using OpenGL of Red Hat Linux 7.x
#CS 420, Tong Yu, Fall 2002

PROG	= icos_subdivide2
#PROG	= icos_subdivide
CFLAGS	= -w -s -O2 -ansi -DSHM
#XLIBS	= -lX11 -lXext -lXmu -lXext -lXmu -lXt -lXi -lSM -lICE
XLIBS	= -lX11 -lXext 
LIBS	= -lglut -lGLU -lGL 
LIBSDL =  -L/usr/local/lib -Wl,-rpath,/usr/local/lib -lSDL 
INCLS	= -I/usr/X11R/include -I/share/mesa/include  -I../mesh
LIBDIR	= -L/usr/X11/lib -L/usr/X11R6/lib 
#source codes
SRCS = $(PROG).cpp  main2.cpp
#substitute .cpp by .o to obtain object filenames
OBJS = $(SRCS:.cpp=.o) 
#OBJS1 =  ../mesh/main.o

#$< evaluates to the target's dependencies, 
#$@ evaluates to the target

$(PROG): $(OBJS)
	g++ -o $@ $(OBJS) $(OBJS1)  $(LIBDIR) $(LIBSDL) $(LIBS) $(XLIBS)

$(OBJS): 
	g++ -c  $*.cpp $(INCLS) 

clean:
	rm $(OBJS) 


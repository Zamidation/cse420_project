LIBSDL =  -L/usr/local/lib -Wl,-rpath,/usr/local/lib -lSDL  -lSDL_image -L./
#use lab 4 Makefile
one: execute
	echo done

execute: objects
	g++ -o project project.o main.o -L./ -lglut -lGLU -lGL

objects: project.o main.o
	echo objects done

project.o: project.cpp
	g++ -c project.cpp #-I/usr/X11R/include

main.o: main.cpp
	g++ -c main.cpp #-I/usr/X11R/include

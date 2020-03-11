LIBSDL =  -L/usr/local/lib -Wl,-rpath,/usr/local/lib -lSDL  -lSDL_image -L./
#use lab 4 Makefile
one: execute
	echo done

earth: execute
	./earth

execute: objects
	g++ -o earth earth.o main2.o -L./ -lglut -lGLU -lGL

objects: earth.o main2.o
	echo objects done

earth.o: earth.cpp
	g++ -c earth.cpp #-I/usr/X11R/include

main2.o: main2.cpp
	g++ -c main2.cpp

clean:
	rm *.o earth

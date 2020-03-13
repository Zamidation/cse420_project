LIBSDL =  -L/usr/local/lib -Wl,-rpath,/usr/local/lib -lSDL  -lSDL_image -L./
#use lab 4 Makefile

# use one of the make commands below:
# make solar_system
# make
# make clean

one: execute
	echo done

solar_system: execute
	./solar_system

execute: objects
	g++ -o solar_system solar_system.o main.o -L./ -lglut -lGLU -lGL

objects: solar_system.o main.o
	echo objects done

earth.o: solar_system.cpp
	g++ -c solar_system.cpp #-I/usr/X11R/include

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o solar_system

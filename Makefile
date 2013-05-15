CC=g++
CFLAGS=-c -Wall #-std=c++11 -std=gnu++11
LIBS=-lGLEW -lGL -lGLU -lglfw
EXECUTABLE=fengine

#Calls fengine which compiles everything as the default action
all: fengine

#Settings for a debug build
debug: CFlAGS+=-DDEBUG -g
debug: EXECUTABLE=fengine_debug
debug: fengine

#Compiles everything
fengine: main.o fengine.o window.o renderer.o
	$(CC) main.o \
	fengine.o \
	window.o \
	renderer.o \
	$(LIBS) \
	-o $(EXECUTABLE)

#Compiles the main file
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

#Compiles the main engine class
fengine.o: fengine.cpp
	$(CC) $(CFLAGS) fengine.cpp

#Compiles the window class
window.o: window.cpp
	$(CC) $(CFLAGS) window.cpp
	
#Compiles the renderer class
renderer.o: renderer.cpp
	$(CC) $(CFLAGS) renderer.cpp

#Clean up the files
clean:
	rm -rf *o $(EXECUTABLE)


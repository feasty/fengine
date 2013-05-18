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
fengine: main.o shader.o fengine.o window.o renderer.o triangle.o matrix.o camera.o object.o model.o
	$(CC) main.o \
	shader.o \
	fengine.o \
	window.o \
	renderer.o \
	triangle.o \
	matrix.o \
	camera.o \
	object.o \
	model.o \
	$(LIBS) \
	-o $(EXECUTABLE)

#Compiles the main file
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
	
#Compiles the shader class
shader.o: base/shader.cpp
	$(CC) $(CFLAGS) base/shader.cpp

#Compiles the main engine class
fengine.o: fengine.cpp
	$(CC) $(CFLAGS) fengine.cpp

#Compiles the window class
window.o: base/window.cpp
	$(CC) $(CFLAGS) base/window.cpp
	
#Compiles the renderer class
renderer.o: base/renderer.cpp
	$(CC) $(CFLAGS) base/renderer.cpp
	
#Compiles the triangle class
triangle.o: shapes/triangle.cpp
	$(CC) $(CFLAGS) shapes/triangle.cpp
	
#Compiles the matrix class
matrix.o: math/matrix.cpp
	$(CC) $(CFLAGS) math/matrix.cpp
	
#Compiles the camera class
camera.o: base/camera.cpp
	$(CC) $(CFLAGS) base/camera.cpp
	
#Compiles the object class
object.o: base/object.cpp
	$(CC) $(CFLAGS) base/object.cpp
	
#Compiles the model class
model.o: base/model.cpp
	$(CC) $(CFLAGS) base/model.cpp

#Clean up the files
clean:
	rm -rf *o $(EXECUTABLE)


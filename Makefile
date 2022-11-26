CC = g++
OUTPUT=main
FLAGS=-lGL -lGLU -lglut -lm -lSOIL -lGLEW


all:
		$(CC) -g *.cpp */*.cpp $(FLAGS) -o $(OUTPUT)
run: all
		./$(OUTPUT)
clear:
		rm *.o -f

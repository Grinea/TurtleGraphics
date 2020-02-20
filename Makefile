CC = gcc
CFLAGS = -ansi -pedantic -Wall -Werror
OBJ1 = turtleGraphics.o fileIO.o effects.o linkedList.o tools.o
OBJ2 = turtleGraphics_simple.o fileIO.o effects.o linkedList.o tools.o
OBJ3 = turtleGraphics_debug.o fileIO.o effects.o linkedList.o tools.o
EXEC1 = TurtleGraphics
EXEC2 = TurtleGraphicsSimple
EXEC3 = TurtleGraphicsDebug

all : $(EXEC1) $(EXEC2) $(EXEC3)

$(EXEC1) : $(OBJ1)
	$(CC) $(OBJ1) -lm -o $(EXEC1)

$(EXEC2) : $(OBJ2)
	$(CC) $(OBJ2) -lm -o $(EXEC2)

$(EXEC3) : $(OBJ3)
	$(CC) $(OBJ3) -lm -o $(EXEC3)

turtleGraphics.o : turtleGraphics.c turtleGraphics.h fileIO.h effects.h \
	linkedList.h tools.h
	$(CC) -c turtleGraphics.c $(CFLAGS)

turtleGraphics_simple.o : turtleGraphics.c turtleGraphics.h fileIO.h \
	effects.h linkedList.h tools.h
	$(CC) -c turtleGraphics.c -Dsimple=1 -o turtleGraphics_simple.o \
	$(CFLAGS)

turtleGraphics_debug.o : turtleGraphics.c turtleGraphics.h fileIO.h \
	effects.h linkedList.h tools.h
	$(CC) -c turtleGraphics.c -Ddebug=1 -o turtleGraphics_debug.o \
	$(CFLAGS)

fileIO.o : fileIO.c fileIO.h turtleGraphics.h linkedList.h tools.h
	$(CC) -c fileIO.c $(CFLAGS)

linkedList.o : linkedList.c linkedList.h turtleGraphics.h
	$(CC) -c linkedList.c $(CFLAGS)

effects.o : effects.c effects.h
	$(CC) -c effects.c $(CFLAGS)

clean :
	rm -f $(OBJ1) $(OBJ2) $(OBJ3) $(EXEC1) $(EXEC2) $(EXEC3)

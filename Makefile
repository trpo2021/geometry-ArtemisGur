CC=gcc
CFLAGS= -Wall -Werror
SOURCES= exception.c MakeTokens.c makeCircle.c printCircle.c circlePerimeter.c circleArea.c
OBJECTS=$(SOURCES:.c=.o)
PATH_SRC= src/libgeometry/
PATH_OBJ= obj/libgeometry/
PATH_BIN= bin/

all: lib
	$(CC) $(CFLAGS) -I src/ src/geometry/geometry.c -L. $(PATH_OBJ)libgeometry.a -o $(PATH_BIN)task

lib: exception.o MakeTokens.o makeCircle.o printCircle.o circleArea.o circlePerimeter.o
	ar rc $(PATH_OBJ)libgeometry.a $(PATH_OBJ)exception.o $(PATH_OBJ)MakeTokens.o $(PATH_OBJ)makeCircle.o $(PATH_OBJ)printCircle.o $(PATH_OBJ)circlePerimeter.o $(PATH_OBJ)circleArea.o
	ranlib $(PATH_OBJ)libgeometry.a

exception.o: 
	$(CC) -c $(CFLAGS) $(PATH_SRC)exception.c -o $(PATH_OBJ)exception.o

MakeTokens.o: 
	$(CC) -c $(CFLAGS) $(PATH_SRC)MakeTokens.c -o $(PATH_OBJ)MakeTokens.o

makeCircle.o: 
	$(CC) -c $(CFLAGS) $(PATH_SRC)makeCircle.c -o $(PATH_OBJ)/makeCircle.o

printCircle.o: 
	$(CC) -c $(CFLAGS) $(PATH_SRC)printCircle.c -o $(PATH_OBJ)printCircle.o

circlePerimeter.o: 
	$(CC) -c $(CFLAGS) $(PATH_SRC)circlePerimeter.c -o $(PATH_OBJ)circlePerimeter.o

circleArea.o: 
	$(CC) -c $(CFLAGS) $(PATH_SRC)circlePerimeter.c -o $(PATH_OBJ)circlePerimeter.o
CC=gcc
CFLAGS= -c -Wall -Wextra -Werror
SOURCES= geometry.c exception.c MakeTokens.c makeCircle.c printCircle.c circlePerimeter.c circleArea.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=test_settings

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

# exception:
# 	$(CC) $(CFLAGS) exception.c -o exception.o

clean:
	rm -rf */*.o *.o test_settings
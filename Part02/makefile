CC = gcc
CFLAGS = -Wall -ansi -pedantic -g
OBJ = main.o map.o color.o random.o newSleep.o
EXEC = ant

ifdef DEBUG_PRINT
CFLAGS += -D DEBUG
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c map.h color.h random.h macros.h newSleep.h
	$(CC) -c main.c $(CFLAGS)

map.o : map.c map.h color.h random.h macros.h
	$(CC) -c map.c $(CFLAGS)

color.o : color.c color.h
	$(CC) -c color.c $(CFLAGS)

random.o : random.c random.h
	$(CC) -c random.c $(CFLAGS)

newSleep.o : newSleep.c newSleep.h
	$(CC) -c newSleep.c $(CFLAGS)

clean :
	rm -f $(OBJ) $(EXEC)
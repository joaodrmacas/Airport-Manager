#Compiler
CC = gcc

#Flags
CFLAGS = -Wall -Wextra -Werror -ansi -pedantic -o

#Executable Name
TARGET = proj2

#C Files
CF = airport.c sortAlgo.c cases.c flights.c checkInput.c booking.c main.c

all:
	$(CC) $(CFLAGS) $(TARGET) $(CF)

clean:
	rm $(TARGET)
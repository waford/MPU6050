#compiler
CC = gcc

#compiler flags
#-g adds debugging info
#-Wall most warnings
CFLAGS = -g -Wall

#Libraries

#Source files
SRCS = $(wildcard *.c)

#Define executable
MAIN = main

default: all

all:
	@echo Compling files
	$(CC) -o $(MAIN) $(SRCS)

clean:
	@echo Cleaning
	rm $(MAIN)

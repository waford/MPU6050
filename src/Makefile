#compiler
CC = gcc

#compiler flags
#-g adds debugging info
#-Wall most warnings
CFLAGS = -g -Wall

#Libraries
LIB = -lm

#Source files
SRCS = $(wildcard *.c)

#Define executable
MAIN = main

default: all

all:
	@echo Compling files
	$(CC) -o $(MAIN) $(SRCS) $(LIB)

clean:
	@echo Cleaning
	rm $(MAIN)

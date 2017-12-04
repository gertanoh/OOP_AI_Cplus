// Makefile

OBJS = State.o List.o StateTest.o ListTest.o
CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall
State.o: State.h
	 $(CC) $(CFLAGS)State.cpp

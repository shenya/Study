#Makefile

CFLAG = -g
CC = gcc
all:
	gcc main.c -o a.out sort_algorithm.c $(CFLAG)

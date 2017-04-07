CFLAGS = -Wall
CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
EXECS = $(patsubst %.c, %, $(SRCS))


.PHONY: all clean


all: $(EXECS)

clean:
	rm -f $(OBJS) $(EXECS)
	clear

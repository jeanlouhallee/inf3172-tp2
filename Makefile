CFLAGS = -Wall -std=gnu11
CC = gcc
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
EXECS = $(patsubst %.c, %, $(SRCS))
DIR = ~/inf3172/bin

.PHONY: all clean


all: $(EXECS)
		if [ ! -d "$(DIR)" ] ; then \
				mkdir -p $(DIR);				\
				mv $(EXECS) $(DIR);			\
		fi																								

clean:
	rm -f $(OBJS) $(EXECS)
	clear

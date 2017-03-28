DIR := ~/inf3172/bin

all: dir tsh

tsh: tsh.o
	gcc -pthread -o $(DIR)/tsh tsh.c
	rm *.o

tsh.o: tsh.c
	clear
	gcc -c tsh.c

dir:
	if [ ! -d $(DIR) ]; then mkdir -p $(DIR); fi;

.PHONY: clean

clean:
	rm -f $(DIR)/tsh
	clear
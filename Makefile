DIR := ~/inf3172/bin

all: dir tsh #new list rmall newdir size fin
	rm *.o
	clear

dir:
	if [ ! -d $(DIR) ]; then mkdir -p $(DIR); fi;


tsh: tsh.o
	gcc -pthread -o $(DIR)/tsh tsh.c

tsh.o: tsh.c
	gcc -c tsh.c


new: new.o
	gcc -pthread -o $(DIR)/new new.c

new.o: new.c
	gcc -c new.c


list: list.o
	gcc -pthread -o $(DIR)/list list.c

list.o: list.c
	gcc -c list.c


rmall: rmall.o
	gcc -pthread -o $(DIR)/rmall rmall.c

rmall.o: rmall.c
	gcc -c rmall.c


newdir: newdir.o
	gcc -pthread -o $(DIR)/newdir newdir.c

newdir.o: newdir.c
	gcc -c newdir.c


size: size.o
	gcc -pthread -o $(DIR)/size size.c

size.o: size.c
	gcc -c size.c


fin: fin.o
	gcc -pthread -o $(DIR)/fin fin.c

fin.o: fin.c
	gcc -c fin.c


.PHONY: clean


clean:
	rm -f $(DIR)/tsh
	#rm -f $(DIR)/new
	#rm -f $(DIR)/list
	#rm -f $(DIR)/rmall
	#rm -f $(DIR)/newdir
	#rm -f $(DIR)/size
	#rm -f $(DIR)/fin
	clear

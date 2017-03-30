DIR := ~/inf3172/bin

all: dir tsh new #list rmall newdir size fin
	rm *.o
	#clear

dir:
	if [ ! -d $(DIR) ]; then mkdir -p $(DIR); fi;


tsh: tsh.o
	gcc -o $(DIR)/tsh tsh.o

tsh.o: tsh.c
	gcc -c -g -W -Wall tsh.c


new: new.o
	gcc -o $(DIR)/new new.o

new.o: new.c
	gcc -c -g -W -Wall new.c


list: list.o
	gcc -o $(DIR)/list list.o

list.o: list.c
	gcc -c -g -W -Wall list.c


rmall: rmall.o
	gcc -o $(DIR)/rmall rmall.o

rmall.o: rmall.c
	gcc -c -g -W -Wall rmall.c


newdir: newdir.o
	gcc -o $(DIR)/newdir newdir.o

newdir.o: newdir.c
	gcc -c -g -W -Wall newdir.c


size: size.o
	gcc -o $(DIR)/size size.o

size.o: size.c
	gcc -c -g -W -Wall size.c


fin: fin.o
	gcc -o $(DIR)/fin fin.o

fin.o: fin.c
	gcc -c -g -W -Wall fin.c


.PHONY: clean


clean:
	rm -f $(DIR)/tsh
	rm -f $(DIR)/new
	#rm -f $(DIR)/list
	#rm -f $(DIR)/rmall
	#rm -f $(DIR)/newdir
	#rm -f $(DIR)/size
	#rm -f $(DIR)/fin
	clear

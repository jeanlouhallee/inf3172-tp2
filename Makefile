tsh: tsh.o
	gcc -pthread -o tsh tsh.c
	rm *.o

tsh.o: tsh.c
	clear
	gcc -c tsh.c

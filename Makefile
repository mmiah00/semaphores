all: control.c main.c
	gcc -o control control.c
	gcc -o write main.c

clean:
	rm -rf *.o

all: clip

clip: main.c
	gcc main.c -o clip

clean:
	rm -f clip
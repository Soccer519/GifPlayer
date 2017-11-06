all:
	gcc -fpic -o libgif/libgif.o -c libgif/gif-decoder.c -L./libgif -lm
	gcc -shared -o libgif/libgif.so libgif/libgif.o -L./libgif -lm
	gcc -o player main.c -I./libgif/ -L./libgif/ -lgif -lbsd

all:
	gcc -fPIC -o libgif/libgif.o -c libgif/gif-decoder.c -L./libgif
	gcc -shared -o libgif/libgif.so libgif/libgif.o -L./libgif
	gcc -rdynamic -o player main.c -I./libgif/ -L./libgif/ -lgif -lbsd

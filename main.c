#include <stdio.h>
#include <stdlib.h>
#include "gif-decoder.h"

int main(void) {
	char *hex_contents = NULL, *ascii_contents = NULL;

	read_file_contents("res/source.gif", &ascii_contents);
	read_file_contents("res/hex_source.txt", &hex_contents);
	extract_header(ascii_contents, NULL, NULL);
	extract_lsd(hex_contents);

	if(hex_contents)
		free(hex_contents);
	if(ascii_contents)
		free(ascii_contents);

	return 0;
}
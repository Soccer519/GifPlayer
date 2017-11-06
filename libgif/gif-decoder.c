#include "gif-decoder.h"

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h> // required by strtonum
#include <bsd/stdlib.h> // strtonum
#include <errno.h>
#include <math.h>

#define DEFAULT_BUFFER_SIZE 512


// Static block lengths
#define HEADER_BYTES 6
#define LSD_BYTES 7


#define LSD_STR_LEN LSD_BYTES * 3


void read_file_contents(char *path, char **out_file_contents) {
	if(*out_file_contents) *out_file_contents = NULL;

	int fd = open(path, O_RDONLY);
	if(fd < 0) {
		fprintf(stderr, "Error opening the file! (%s)\n", strerror(errno));
		return;
	}

	char buf[DEFAULT_BUFFER_SIZE];
	int rbytes, nbytes;
	do {
		rbytes = read(fd, buf, DEFAULT_BUFFER_SIZE);
		buf[rbytes] = '\0';
		nbytes += rbytes;
		*out_file_contents = realloc(*out_file_contents, nbytes);
		strncat(*out_file_contents, buf, rbytes);
	} while(rbytes == (ssize_t)DEFAULT_BUFFER_SIZE);

	close(fd);
}


// Needs to recieve the non-hex file as a parameter for file_contents
void extract_header(char *ascii_contents, char *out_sig, char *out_ver) {
	char header_block[HEADER_BYTES + 1]; // +1 for null terminator
	strncpy(header_block, ascii_contents, HEADER_BYTES);
	header_block[HEADER_BYTES] = '\0';

	if(!out_sig || !out_ver) {
		char signature[4], version[4];
		strncpy(signature, header_block, 3);
		strncpy(version, (header_block + 3), 3);
		signature[3] = '\0';
		version[3] = '\0';

		printf("Signature: %s, Version: %s\n", signature, version);
	} else {
		out_sig = malloc(4);
		out_ver = malloc(4);
		strncpy(out_sig, header_block, 3);
		strncpy(out_ver, (header_block + 3), 3);
		*(out_sig + 3) = '\0';
		*(out_ver + 3) = '\0';
	}
}

void extract_lsd(char *hex_contents) {
	char lsd_block[LSD_STR_LEN + 1];
	strncpy(lsd_block, (hex_contents + HEADER_BYTES * 3), LSD_STR_LEN);
	lsd_block[LSD_STR_LEN] = '\0';

	int width, height;
	width = height = 0;

	char tmp[5];
	strncpy(tmp + 2, lsd_block, 2);
	strncpy(tmp, lsd_block + 3, 2);
	tmp[4] = '\0';
	width = (int)strtol(tmp, NULL, 16);

	strncpy(tmp + 2, lsd_block + 6, 2);
	strncpy(tmp, lsd_block + 9, 2);
	tmp[4] = '\0';
	height += (int)strtol(tmp, NULL, 16);

	strncpy(tmp, lsd_block + 12, 2);
	tmp[2] = '\0';
	printf("%s\n", tmp);
	int packed_field = (int)strtol(tmp, NULL, 16);
	printf("%d\n", packed_field);
}
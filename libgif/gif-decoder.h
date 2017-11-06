#ifndef _GIF_DECODER
#define _GIF_DECODER

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h> // required by strtonum
#include <bsd/stdlib.h> // strtonum
#include <errno.h>

void read_file_contents(char *path, char **out_file_contents);
void extract_header(char *ascii_contents, char *out_sig, char *out_ver);
void extract_lsd(char *hex_contents);
void extract_color_table(char *hex_contents);

#endif
#ifndef _GIF_DECODER
#define _GIF_DECODER

void read_file_contents(char *path, char **out_file_contents);
void extract_header(char *ascii_contents, char *out_sig, char *out_ver);
void extract_lsd(char *hex_contents);

#endif
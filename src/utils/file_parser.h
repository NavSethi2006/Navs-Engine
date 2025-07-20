#ifndef TMX_PARSER_H
#define TMX_PARSER_H

#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern char* read_file(const char* path);
extern char* find_tag(const char* xml, const char* tag);
extern int extract_attr_int(const char* tag, const char* attr);
extern float extract_attr_float(const char *tag, const char* attr);
extern char* extract_csv_data(const char* data_tag);
extern void parse_csv(const char* csv, int* tiles, int max);
extern void extract_attr_string(const char* tag, const char* attr, char* dest, int max_len);

#endif
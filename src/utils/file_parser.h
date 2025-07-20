#ifndef TMX_PARSER_H
#define TMX_PARSER_H

#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char* read_file(const char* path);
static char* find_tag(const char* xml, const char* tag);
static int extract_attr_int(const char* tag, const char* attr);
static char* extract_csv_data(const char* data_tag);
static void parse_csv(const char* csv, int* tiles, int max);

#endif
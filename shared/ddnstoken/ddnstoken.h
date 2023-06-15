#include <stdio.h>
#include <stdlib.h>

#define DDNSTOKEN

#include "py/builtin.h"

long get_file_size(FILE* file);
unsigned char* read_file_to_memory(const char* file_path, long* file_size);
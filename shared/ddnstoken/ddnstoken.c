/*
 * This file is part of the DDNSToken project, https://ddnstoken.com/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2023 Certchip
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "ddnstoken.h"

long get_file_size(FILE* file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    return size;
}

unsigned char* read_file_to_memory(const char* file_path, long* file_size) {
    FILE* file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("Failed to open file: %s\n", file_path);
        return NULL;
    }

    long size = get_file_size(file);
    unsigned char* buffer = (unsigned char*)malloc(size + 1);
    if (buffer == NULL) {
        fclose(file);
        printf("Failed to allocate memory for file: %s\n", file_path);
        return NULL;
    }

    size_t read_size = fread(buffer, 1, size, file);
    if (read_size != (size_t)size) {
        fclose(file);
        free(buffer);
        printf("Failed to read file: %s\n", file_path);
        return NULL;
    }

    buffer[size] = '\0'; // 파일 데이터 마지막에 널 문자 추가

    fclose(file);
    *file_size = size;
    return buffer;
}

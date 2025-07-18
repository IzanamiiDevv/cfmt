#ifndef FMT_H
#define FMT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define FMT_DEVELOPER "IzanamiiDevv"
#define FMT_STORAGE_CAPACITY 1024

static char* __fmt_storage[FMT_STORAGE_CAPACITY];
static int __fmt_storage_count = 0;
static void __fmt_track(char* ptr) {
    if (__fmt_storage_count < FMT_STORAGE_CAPACITY) {
        __fmt_storage[__fmt_storage_count++] = ptr;
    }
}
void strfmtA(char** holder, const char* format, ...) {
    va_list args;
    va_start(args, format);
    va_list args_copy;
    va_copy(args_copy, args);
    int len = vsnprintf(NULL, 0, format, args_copy);
    va_end(args_copy);

    char* buffer = (char*)malloc(len + 1);
    if (!buffer) {
        *holder = NULL;
        va_end(args);
        return;
    }

    vsnprintf(buffer, len + 1, format, args);
    va_end(args);

    *holder = buffer;
    __fmt_track(buffer);
}

char* strfmtB(const char* format, ...) {
    va_list args;
    va_start(args, format);
    va_list args_copy;
    va_copy(args_copy, args);
    int len = vsnprintf(NULL, 0, format, args_copy);
    va_end(args_copy);

    char* buffer = (char*)malloc(len + 1);
    if (!buffer) {
        va_end(args);
        return NULL;
    }

    vsnprintf(buffer, len + 1, format, args);
    va_end(args);

    __fmt_track(buffer);
    return buffer;
}

void fmtfree() {
    for (int i = 0; i < __fmt_storage_count; ++i) {
        free(__fmt_storage[i]);
        __fmt_storage[i] = NULL;
    }
    __fmt_storage_count = 0;
}

#endif
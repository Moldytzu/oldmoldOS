#pragma once
#include <stdint.h>

int strlen(const char* str);
int strcmp(const char* a, const char* b);
char* itoa(uint64_t value, char* result, int base);
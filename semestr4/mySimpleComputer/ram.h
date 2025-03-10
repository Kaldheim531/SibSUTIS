#include<stdio.h>
#include <stdlib.h>
#define MEMORY_SIZE 128
static int memory[128];
int sc_memoryInit (void);
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int *value);
int sc_memorySave(const char *filename);
int sc_memoryLoad(const char *filename);
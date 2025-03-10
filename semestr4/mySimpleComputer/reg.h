#include<stdio.h>
#define FLAG_OVERFLOW 0x1
#define FLAG_DIVISION_BY_ZERO 0x2
#define FLAG_MEMORY_ERROR 0x4
#define FLAG_INVALID_COMMAND 0x8
#define FLAG_IGNORE_CLOCK 0x10

int sc_regInit(void);
int sc_regSet(int reg, int value);
int sc_regGet(int reg, int *value);
int sc_accumulatorInit(void);
int sc_accumulatorSet(int value);
int sc_accumulatorGet(int *value);
int sc_icounterInit(void);
int sc_icounterSet(int value);
int sc_icounterGet(int *value);


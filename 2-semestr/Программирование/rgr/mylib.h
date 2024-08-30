#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>

void swap(wchar_t *x, wchar_t *y);
void permute(wchar_t *a, int l, int r, FILE *F2);
#include "mylib.h"



int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: ./a.out N\n");
        return -1;
    }

    char *f = argv[1];  // Anagrama.txt
    char *f2 = argv[2]; // Answer.txt

    setlocale(LC_ALL, "ru_RU.UTF-8");

    if (!setlocale(LC_ALL, "ru_RU.UTF-8")) {
    printf("Error setting locale\n");
    return 1;
}

    FILE *file = fopen(f, "r");

    if (file == NULL)
    {
        printf("Error opening file %s for reading\n", f);
        return 1;
    }

    int size = 0;
    wchar_t c;
    while ((c = fgetwc(file)) != WEOF)
    {
        size++;
    }
    rewind(file);

    wchar_t *line = (wchar_t *)malloc((size + 1) * sizeof(wchar_t));
    if (line == NULL)
    {
        printf("Memory allocation failed for word.\n");
        fclose(file);
        return 1;
    }
    for (int i = 0; i < size; i++)
    {
        c = fgetwc(file);
        if (c == WEOF)
        {
            printf("Error reading word from input file.\n");
            free(line);
            fclose(file);
            return 1;
        }
        line[i] = c;
    }
    line[size] = L'\0';
    wprintf(L"%ls\n", line);

    printf("длина слова %d\n", size);

    fclose(file);

    FILE *F2 = fopen(f2, "w");
    if (F2 == NULL)
    {
        printf("Error opening file %s for writing\n", f2);
        free(line);

        return 1;
    }
    permute(line, 0, size - 1, F2);
    free(line);

    fclose(F2);

    return 0;
}
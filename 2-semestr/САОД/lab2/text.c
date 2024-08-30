#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100000

int compare_words(const void *a, const void *b)
{
    return strcmp(*(char *const *)a, *(char *const *)b);
}

int main()
{
    char words = (char **)malloc(sizeof(char *));
    char word[10];
    int num_words = 0;

    FILE *file = fopen("words.txt", "r");

    if (file == NULL)
    {
        printf("Ошибка открытия файла\n");
        return 1;
    }

    while (fscanf(file, "%s", word) == 1)
    {
        strcpy(words[num_words], word);
        num_words++;
    }

    fclose(file);

    // Сортировка слов в алфавитном порядке
    qsort(words, num_words, sizeof(words[0]), compare_words);

    // Вывод отсортированных слов
    for (int i = 0; i < num_words; i++)
    {
        printf("%s ", words[i]);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1004



int main()
{

    FILE *file1;

    file1 = fopen("input.txt", "w");

    int line_count = 0;
    printf("Введите количество строк для записи в файл: ");
    scanf("%d", &line_count);

    for (int i = 0; i < line_count; i++)
    {
        char word[MAX_LINE_LENGTH];
        printf("Введите строку %d : ", i + 1);
        scanf("%s", word);
        printf("\n");
        fprintf(file1, "%s ", word);
    }

    printf("Файл успешно создан с %d строками\n", line_count);

    fclose(file1);


    FILE *file2 = fopen("input.txt", "r");
    char **words = (char **)malloc(line_count * sizeof(char *)); // массив строк

    for (int i = 0; i < line_count; i++)
    {
        words[i] = (char *)malloc(MAX_LINE_LENGTH * sizeof(char)); 
    }

    char line[MAX_LINE_LENGTH];
    int word_count = 0;

    while (fgets(line, MAX_LINE_LENGTH + 1, file2))
    {
        char *word = strtok(line, " ");

        while (word != NULL)
        {
            strcpy(words[word_count], word);
            word_count++;
            word = strtok(NULL, " ");
        }
    }

    fclose(file2);

    FILE *file3 = fopen("output.txt", "w");

    // Вывод слов на экран
    for (int i = 0; i < word_count; i++)
    {
        printf("%s\n", words[i]);
    }
    
    for (int i = 0; i < word_count / 2; i++)
    {
        char *temp = words[i];
        words[i] = words[word_count - i - 1];
        words[word_count - i - 1] = temp;

    }

     printf("\n");


    // Вывод слов на экран
    for (int i = 0; i < word_count; i++)
    {
        printf("%s \n", words[i]);
        fprintf(file3, "%s ",words[i]);
    }

}

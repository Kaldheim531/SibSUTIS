#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 50100
#define MAX_WORD_LENGHT 5
int main(){
    
    char **words = (char **)malloc(N * sizeof(char *)); // массив строк

    for (int i = 0; i < N; i++)
    {
        words[i] = (char *)malloc(5 * sizeof(char)); // каждая строка длиной 5 символов (четыре буквы + нулевой символ)
    }

    FILE *file = fopen("output_desc.txt", "r");

    if (file == NULL){
        printf("Ошибка открытия файла\n");
        return 1;
    }

    
    char word[5];

    for (int num_words = 0;fscanf(file, "%s", word) == 1;num_words++)
    {

        strcpy(words[num_words], word);
        
       /* printf("%s %d\n",words[num_words],num_words);*/
    }

    fclose(file);
    printf("массив заполнен");
    puts("\n");
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
}
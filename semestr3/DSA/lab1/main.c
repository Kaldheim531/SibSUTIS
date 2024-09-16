#include "rbtrees.h"
#define N 50100
#define MAX_WORD_LENGHT 5


int main() 
{
    srand(time(NULL));

    int min = 0;
    int max = N;
    char **words = (char **)malloc(N * sizeof(char *)); // массив строк
    for (int i = 0; i < N; i++)
    {
        words[i] = (char *)malloc(5 * sizeof(char)); // каждая строка длиной 5 символов (четыре буквы + нулевой символ)
    }

    FILE *file = fopen("output_asc.txt", "r");
    if (file == NULL){
        printf("Ошибка открытия файла\n");
        return 1;
    }

    int num_words = 0;
    char word[5];

    while (fscanf(file, "%s", word) == 1)
    {

        strcpy(words[num_words], word);
        num_words++;
    }
    fclose(file);

    printf("массив заполнен");
    puts("\n");
    return 0;

    for (int i = 2, m = 0; i <= 200000; i++)
    {
        bstree_add(tree1, words[i - 1], i - 1);
       

        if (i % 10000 == 0)
        {
            m += 1;

            // trie
            double total_time_trie = 0;

            for (int j = 0; j <= i; j++)
            {
                double start = wtime();
                char *w = words[getrand(0, i - 1)];
                struct bstree *node1 = bstree_lookup(tree1, w);
                double end = wtime();
                total_time_trie += end - start;
            }
            double timer1 = total_time_trie / i;

            // print

            printf("\n%.2d   n = %.6d; trie_lkup_time = %.9f ", m, i, timer1);
            FILE *file1 = fopen("lookup_time.dat", "a");
            fprintf(file1, "%d %.8f \n", i, timer1);
            fclose(file1);
        }
    }
    
}
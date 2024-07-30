#include "bstree.h"
#include "hashtab.h"
#define N 250003
#define MAX_WORD_LENGTH 5
#define size 200003
int compare_words(const void *a, const void *b)
{
    return strcmp(*(char *const *)a, *(char *const *)b);
}
int is_duplicate(char **words, int num_words, char *word)
{
    for (int i = 0; i < num_words; i++)
    {
        if (strcmp(words[i], word) == 0)
        {
            return 1; // Дубликат найден
        }
    }
    return 0; // Дубликат не найден
}

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

    FILE *file = fopen("unique.txt", "r");
    if (file == NULL)
    {
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

    /*  qsort(words, i, sizeof(char *), compare_words);

    FILE *file2 = fopen("words3.txt", "w");

    for (int j = 0; j < i; j++)
    {
        fprintf(file2, "%s ", words[j]);
    }

    fclose(file2);
    */

    printf("массив заполнен");
    printf("\n");
    /**/
    // эксперимент 1 0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
    /**/
    printf("\n");
    printf("Эксперимент 1 lookup ");
    printf("\n");

     struct listnode *hashtab1[size + 1];
    hashtab_init(hashtab1);

    struct bstree *tree1 = bstree_create(words[0], 0);

    for (int i = 2, m = 0; i <= 200000; i++)
    {
        bstree_add(tree1, words[i - 1], i - 1);
        hashtab_add(hashtab1, words[i - 1], i - 1);

        if (i % 10000 == 0)
        {
            m += 1;

            // trie
             double start = wtime();

            for (int j = 0; j <= i; j++)
            {
                
                char *w = words[getrand(0, i - 1)];
                struct bstree *node1 = bstree_lookup(tree1, w);
                
                total_time_trie += end - start;
            }
            double end = wtime();
            double timer1 = total_time_trie / i;

            // HASH

            double total_time_hash = 0;

            for (int j = 0; j <= i; j++)
            {
                double start = wtime();
                char *w = words[getrand(0, i - 1)];
                struct listnode *node2 = hashtab_lookup(hashtab1, w);
                double end = wtime();
                total_time_hash += end - start;
            }

            double timer2 = total_time_hash / i;

            // print

            printf("\n%.2d   n = %.6d; trie_lkup_time = %.9f hash_lkup_time = %.10f", m, i, timer1, timer2);
            FILE *file1 = fopen("lookup_time.dat", "a");
            fprintf(file1, "%d %.8f %.10f\n", i, timer1, timer2);
            fclose(file1);
        }
    }


}

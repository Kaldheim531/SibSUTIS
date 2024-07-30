#include "bstree.h"
#include "hashtab.h"
#define N 250003
#define MAX_WORD_LENGTH 5
#define size 200003

int compareStrings(const void *a, const void *b)
{
    return -strcmp(*(const char **)a, *(const char **)b);
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

    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    
    

    char **words1 = (char **)malloc(N * sizeof(char *)); // массив строк

    for (int i = 0; i < N; i++)
    {
        words1[i] = (char *)malloc(5 * sizeof(char)); // каждая строка длиной 5 символов (четыре буквы + нулевой символ)
    }

    FILE *file10 = fopen("myunique.txt", "r");

    int num_words1 = 0;
    char word1[5];

    while (fscanf(file10, "%s", word1) == 1)
    {

        strcpy(words1[num_words1], word1);
        num_words1++;
    }
    fclose(file10);
    
    

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
    /*
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

    printf("\n");
     // эксперимент 4 |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
   
   /* 
    printf("\n");
    printf("Эксперимент 4 lookup ");
    printf("\n");

    
    for (int i = 10000, m = 0; i <= 200000; i+=10000)
    {   
        m+=1;
        double total_time_trie = 0;
        struct bstree *tree2 = bstree_create(words1[0], 0); //создаем бинарное дерево
        
        struct bstree *tree6 = bstree_create(words[0], 0); //создаем бинарное дерево

        for (int j = 0; j <= i; j++)   //Анализ поведения в худшем случае: добавить в словарь n слов в порядке их невозрастания  после чего замерить время поиска минимальногоключа.
        {
            double start_time = wtime();
               //худший случай
            char *w = words1[getrand(0, i - 1)];
            struct bstree *node1 = bstree_lookup(tree2, w);
            double end_time = wtime();
            total_time_trie += (end_time - start_time);
        }
        double timer1 = total_time_trie;



        double total_time_bstree = 0;    //Анализ поведения в среднем случае: добавить в словарь n слов и замерить время поиска минимального ключа.
        for (int j = 0; j <= i; j++)
        {
            double start_time = wtime();
             bstree_min(tree6); //средний случай
            double end_time = wtime();
            total_time_bstree += (end_time - start_time);
        }
        double timer2 = total_time_bstree;

        // print
        printf("\n%.2d  n = %.6d; bstree_worst_time = %.9f bstree_avg_time = %.11f", m, i, timer1, timer2);

        FILE *file2 = fopen("add_time.dat", "a");
        fprintf(file2, "%d %.9f %.9f \n", i, timer1, timer2);
        fclose(file2);
    }
    printf("\n");
    printf("\n");


    // эксперимент 6 KP Add 0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
    /**/
    // Сравнение времени поска в хэштаблице от хэшфункций и количества коллизий
    printf("Эксперимент 6 KP FNV ");
    printf("\n");
    printf("\n");

    struct listnode *hashtab_KP[size + 1];
    hashtab_init(hashtab_KP);

    struct listnode *hashtab_FNV[size + 1];
    hashtab_init(hashtab_FNV);

    int collisions_KP = 0;
    int collisions_FNV = 0;

    for (int i = 2, m = 0; i <= 200000; i++)
    {

        hashtab_add_KP(hashtab_KP, words[i - 1], i - 1, &collisions_KP);

        hashtab_add_FNV(hashtab_FNV, words[i - 1], i - 1, &collisions_FNV);

        if (i % 10000 == 0)
        {
            m += 1;

            // KP

            double total_time_KP = 0;
            for (int j = 0; j <= i; j++)
            {
                double start = wtime();
                char *w2 = words[getrand(0, i - 1)];
                struct listnode *node2 = hashtab_lookup(hashtab_KP, w2);
                double end = wtime();
                total_time_KP += end - start;
            }

            double timer1 = total_time_KP / i;

            // FNV

            double total_time_FNV = 0;
            for (int j = 0; j <= i; j++)
            {
                double start = wtime();
                char *w3 = words[getrand(0, i - 1)];
                struct listnode *node3 = hashtab_lookup_FNV(hashtab_FNV, w3);
                double end = wtime();
                total_time_FNV += end - start;
            }

            double timer2 = total_time_FNV / i;
            ;

            // print

            printf("%.2d n = %.6d; KP_lkup_time = %.9f FNV_lkup_time = %.9f KP_collis = %.2d ,FNV_collis = %.2d\n", m, i, timer1, timer2, collisions_KP, collisions_FNV);

            FILE *file3 = fopen("hash_lookup.dat", "a");
            fprintf(file3, "%d %.8f %.8f %d %d\n", i, timer1, timer2, collisions_KP, collisions_FNV);
            fclose(file3);
        }
    }
}

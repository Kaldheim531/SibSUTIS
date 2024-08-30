#include "bstree.h"
#include "hashtab.h"
#define N 250000
#define MAX_WORD_LENGTH 5
int compare_words(const void *a, const void *b);
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
    /*
    // эксперимент 1 0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
    printf("Эксперимент 1 lookup ");
    printf("\n");

    struct listnode *hashtab[N];
    hashtab_init(hashtab);

    struct bstree *tree = bstree_create(words[0], 0);

    for (int i = 2, m = 0; i <= 200000; i++)
    {

        bstree_add(tree, words[i - 1], i - 1);
        hashtab_add(hashtab, words[i - 1], i - 1);
        if (i % 10000 == 0)
        {
            m += 1;
            // hast_table |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
            char *w2 = words[getrand(0, i - 1)];

            long double timer2 = wtime();
            for(int i=0;i<N-1;i++){
            struct listnode *node2 = hashtab_lookup(hashtab, w2);
            }

            timer2 = wtime() - timer2;

            // trie |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
            char *w = words[getrand(0, i - 1)];

            double timer1 = wtime();
            struct bstree *node = bstree_lookup(tree, w);
            timer1 = wtime() - timer1;

            // print |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

            printf("\n%.2d   n = %d; trie_lkup_time = %.9f hash_lkup_time = %.9Lf", m, i, timer1, timer2);
            FILE *file = fopen("lookup.dat", "a");
            fprintf(file, "%.2d %d %.15f %.15f\n", m, i, timer1, timer2);
            fclose(file);
        }
    }*/
    printf("\n");
    // эксперимент 2 |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    /*
    printf("\n");
    printf("Эксперимент 2 add ");
    printf("\n");

    struct listnode *hashtab2[N];
    hashtab_init(hashtab2);

    

    for (int i = 10000, m = 0; i <= 200000; i += 10000)
    {   m+=1;

        //trie
        struct bstree *tree2 = bstree_create(words[0], 0);
        for (int j = 0; j < i; j++)
        {
            bstree_add(tree2, words[j], j);
        }

        double timer1 = wtime();
        bstree_add(tree2, words[i], i);
        timer1 = wtime() - timer1;

        //hash
        
        
        for (int j = 0; j < i; j++)
        {   
            hashtab_add(hashtab2, words[j], j);
            
        }
        
        double timer2 = wtime();
        hashtab_add(hashtab2, words[i], i);
        timer2 = wtime() - timer2;

       
        
        
        //print
        printf("\n%.2d  n = %.6d; trie_add_time = %.9f hash_add_time = %.11f", m, i, timer1, timer2);
        
        
        FILE *file2 = fopen("add.dat", "w");
        fprintf(file2, "%d %.9f %.9f \n",i,timer1, timer2);
        fclose(file2);
    }
    printf("\n");
     printf("\n");
    // эксперимент 6 KP ELF  0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
    /*
    printf("Эксперимент 6 KP ELF ");
    printf("\n");
    printf("\n");

    struct listnode *hashtab_KP[N];
    hashtab_init(hashtab_KP);

    struct listnode *hashtab_ELF[N];
    hashtab_init(hashtab_ELF);
    

    int collisions_KP = 0;
    int collisions_ELF = 0;

    for (int i = 2, m = 0; i <= 200000; i++)
    {

        hashtab_add_KP(hashtab_KP, words[i - 1], i - 1,&collisions_KP);

        hashtab_add_ELF(hashtab_ELF, words[i - 1], i - 1,&collisions_ELF);

 
        if (i % 10000 == 0)
        {
         m += 1;

            // KP
            char *w2 = words[getrand(0, i - 1)];
            double timer1 = wtime();
            //for(int b=0;b<N-1;b++){}
                struct listnode *node2 = hashtab_lookup(hashtab_KP, w2);
            timer1 = wtime() - timer1;

            // ELF
            char *w3 = words[getrand(0, i - 1)];
            double timer2= wtime();
            //for(int c=0;c<N-1;c++){}
                struct listnode *node3 = hashtab_lookup_ELF(hashtab_ELF, w3);
            timer2 = wtime() - timer2;


  
            // print

            printf("%.2d n = %.6d; KP_lkup_time = %.7f ELF_lkup_time = %.7f KP_collis = %.2d ,ELF_collis = %.2d\n", m, i, timer1,timer2,collisions_KP,collisions_ELF);

            FILE *file3 = fopen("hash_lookup.dat", "w");
            fprintf(file3, "%d %.8f %.8f %d %d\n", i, timer1,timer2,collisions_KP,collisions_ELF);
            fclose(file3);
        }
    }*/
}

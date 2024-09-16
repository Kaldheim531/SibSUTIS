#include "rbtrees.h"
#define N 50100
#define MAX_WORD_LENGHT 5


int main() 
{
    srand(time(NULL));

    
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

    for (int num_words = 0;fscanf(file, "%s", word) == 1 && num_words < N;num_words++)
    {

        strcpy(words[num_words], word);
        
       /* printf("%s %d\n",words[num_words],num_words);*/
    }

    fclose(file);
    printf("массив заполнен");
    puts("\n");
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    

    struct rbtree *root = NULL;

    for (int i = 2, m = 0; i <= 50002; i++)
    {
         root = rbtree_add(root, i-1, words[i-1]);


        if (i % 5000 == 0)
        {
            m += 1;
            double start = wtime();
            root = rbtree_add(root, i-1, words[i-1]);
            double end = wtime();

            printf("\n%.2d   n = %.5d; rbtree_lkup = %.9f ", m, i, end-start);

            /*FILE *file1 = fopen("lookup_time.dat", "a");
            fprintf(file1, "%d %.8f \n", i, timer1);
            fclose(file1);*/   
                
        }
    }

    puts("\nВставка завершена\n");
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   
   for (int i = 0; i < N; i++)
    {
        free(words[i]);
    }
    free(words);
    
}
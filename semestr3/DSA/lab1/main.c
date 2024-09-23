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
    

    struct rbtree *tree = NULL;

    for (int i = 2, m = 0; i <= 50002; i++)
    {
         tree = rbtree_add(tree, i-1, words[i-1]);
         int height = black_height(tree);
         printf("Номер узла: %d, черная высота: %d\n", i + 1, height);
         //check_rbtree_properties(tree);

    }

   
   
    
    puts("\nВставка завершена\n");
    
    printf("Элемент %s\n",words[2225]);

    struct rbtree *look =  rbtree_lookup(tree, 2225);
    printf("Поиск элемента %s\n",look->value);

    
    struct rbtree *root = NULL;

    root = rbtree_add(root, 14, "aaab");
    root = rbtree_add(root, 11, "aaac");
    root = rbtree_add(root, 15, "fsdf");
    root = rbtree_add(root, 2, "jbff");
    root = rbtree_add(root, 1, "wwww");
    root = rbtree_add(root, 7, "ssss");
    root = rbtree_add(root, 5, "aaaa");
    root = rbtree_add(root, 8, "gggg");

    
   // check_rbtree_properties(root);
    rbtree_print_dfs(root, 0);

   
    root = rbtree_delete(root, 8);

    
    puts("Дерево после удаления элемента:");

    //check_rbtree_properties(root);
    rbtree_print_dfs(root, 0);
     
     
    for (int i = 0; i < N; i++)
    {
        free(words[i]);
    }
    free(words);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   
   
    
}
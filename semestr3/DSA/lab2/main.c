#include"trie.h"
#define N 50100
#define MAX_WORD_LENGHT 14
#define d 26
#define NUM_KEYS 10000
#define KEY_LENGTH 10

int main() 
{
    
    srand(time(NULL));
    
    char **words = (char **)malloc(N * sizeof(char *)); // массив строк

    for (int i = 0; i < N; i++)
    {
        words[i] = (char *)malloc(14 * sizeof(char)); // каждая строка длиной 5 символов (четыре буквы + нулевой символ)
    }

    FILE *file = fopen("output_desc.txt", "r");

    if (file == NULL){
        printf("Ошибка открытия файла\n");
        return 1;
    }

    
    char word[14];

    for (int num_words = 0;fscanf(file, "%s", word) == 1 && num_words < N;num_words++)
    {

        strcpy(words[num_words], word);
        
       /* printf("%s %d\n",words[num_words],num_words);*/
    }

    fclose(file);
    printf("массив заполнен");
    puts("\n");

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   struct trie*  tree2 = trie_create();

    tree2=trie_insert(tree2, "Tigr","180");
    tree2=trie_insert(tree2, "Tapir","300");
    tree2=trie_insert(tree2, "Barsuk","15");
    tree2=trie_insert(tree2, "Barnaul","440");
    tree2=trie_insert(tree2, "Bars","55");

    char* tree2lkp = trie_lookup(tree2, "Barsuk");
    printf("%s\n",tree2lkp);
    trie_print(tree2, 0);
     


    // Удаление ключа "Barsuk"
    tree2 = trie_delete(tree2, "Barsuk");

    // Вывод дерева после удаления
    printf("\nДерево после удаления ключа 'Barsuk':\n");
    trie_print(tree2, 0);
   

  


    
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   for (int i = 0; i < N; i++)
    {
        free(words[i]);
    }

    free(words);
   
    
}
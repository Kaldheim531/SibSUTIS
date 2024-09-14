#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define min 97
#define max 122
int main(){
  srand(time(NULL));

  FILE *words=fopen("words.txt","w");
  if(words==NULL){
    puts("Ошбка открытия файла");
    return 0;}

  for(int i=0;i<51000;i++){
    char str[4];
    for(int i=0;i<4;i++){
      str[i]= min + rand() % (max - min + 1);
    }
    fprintf(words,"%s\n",str);

  }
  fclose(words);
}
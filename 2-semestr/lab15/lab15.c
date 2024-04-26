#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 10

typedef struct

{   char FIO[50];
    char phonenumber[11];
    
}abonent;

int main()
{

    FILE *file = fopen("ABONENT.dat", "wb");

     abonent people[N]=
    {
        {"Петров П А","89123456789",},
        {"Сидоров А.И.","89012345678"},
        {"Кузнецов С.В.","89765432109"},
        {"Смирнов А.П.","89567894567"},
        {"Васильева","89456789012"},
        {"Козлова Е.М.","89987654321"},
        {"Новиков П.С.","89321098765"},
        {"Морозова Е.В.","89234567890"},
        {"Волкова Л.К.","89109876543"},
        {"Алексеев И.С.","89987654321"},

    };
    
     
    for(int i = 0; i < N; i++){
        fwrite(&people[i], sizeof(abonent), 1, file);
        //printf("Номер телефона: %s   \n  ", people[i].phonenumber);
       // printf("FIO: %s   \n  ", people[i].FIO);
    }


    fclose(file);

    memset(people, 0, sizeof(*people));

    char found_FIO[50];
    printf("Введите ФИО: ");
    fgets(found_FIO, sizeof(found_FIO), stdin);
    found_FIO[strcspn(found_FIO, "\n")] = 0; 
    //scanf("%s",found_FIO);
    printf("%s\n",found_FIO);
    

    file = fopen("ABONENT.dat", "rb");

    abonent current_abonent;
    int found = 0;
    //printf("%s\n",current_abonent.FIO);
    while(fread(&current_abonent, sizeof(abonent), 1, file)){
        if(strcmp(current_abonent.FIO, found_FIO) == 0){
            printf("Номер телефона: %s   \n  ", current_abonent.phonenumber);
            found = 1;
        }
    }

    if (!found){

        printf("Такого абонента нет\n");
    }

    fclose(file);
    
}

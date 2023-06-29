#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 // функция удаления знака '\n'
char * str_change(char* str) 
{
    int len = strlen(str);
    if (len > 0 && str[len - 1 ] == '\n')
        str[len - 1] = '\0';
    return str;
}

int main(int argc, char *argv[]) 
{
    FILE *file1, *file2;
    char line1[100], line2[100];

 // проверка количества аргументов 
    if (argc != 3) 
    {
        printf("enter like: file1 file2");
        return 1;
    }

    file1 = fopen(argv[1], "r");
    file2 = fopen(argv[2], "r");
//  проверка открытия файла 
    if (file1 ==NULL || file2 == NULL)
    {
        printf("File opening error\n");
        return 1;
    }
// построчная запись
    while (fgets(line1, 100, file1) != NULL && fgets(line2, 100, file2) != NULL) 
    {
        puts(str_change(line1));
        puts(str_change(line2));
    }


    // в случае если один из файлов закончился 

    while (fgets(line1, 100, file1) != NULL) 
        printf("%s", line1);

    while (fgets(line2, 100, file2) != NULL) 
        printf("%s", line2); 

    fclose(file1);
    fclose(file2);
    free(line1);
    free(line2);

    return 0; 
}
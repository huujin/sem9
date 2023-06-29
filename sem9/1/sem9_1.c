#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1000

// функция tail() с аргументами char *filename, int n
void tail(char *filename, int n) 
{
    FILE *file = fopen(filename, "r");

    // вторая проверка аргумента командной строки 
    if(file == NULL) 
    {
        printf("Error opening file %s\n", filename);
        exit(-1);
    }

    char lines[n][MAX_LINE_LENGTH];
    int current_line = 0;

    while(fgets(lines[current_line % n], MAX_LINE_LENGTH, file) != NULL)
        current_line++;

    int i;
    int start = current_line - n;

    if(start < 0)   start = 0;

    for(i = start; i < current_line; i++) 
        printf("%s", lines[i % n]);

    fclose(file);

}
// изменения: указаны проверка аргументов командной строки

// int argc, char *argv[] - аргументы камандной строки
int main(int argc, char *argv[]) 
{
    // проверка количесво аргуметом - должен быть задан файл
    if(argc < 2) 
    {
        printf("Usage: %s filename [n]\n", argv[0]);
        exit(-1);
    }

    char *filename = argv[1];
    int n = 5;

    if(argc >= 3) 
    {
        n = atoi(argv[2]);  // необязательный аргумент n - последние n  строки
        if (n <=  0)
        {
            printf("n cannot be negative");
            exit(1);
        }
    }

    tail(filename, n);

    return 0;
}



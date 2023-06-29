
#include <stdlib.h>
#include <stdio.h>

// изменения добавлены проверки аргументов командной строки

// функция read_string считывает символы из file и сохраняет в buffer размером n 
void read_string(FILE *file, char *buffer, int n) 
{ 
    int buf, i;
    for (i = 0; i < n - 1; i++) 
    {
        buf = fgetc(file); 
        if ((buf == '\n') || (buf == EOF)) 
        {
            buffer[i] = '\0';
            if ((i == 0) && (buf == '\n')) // если первый символ == '\n' то строка не используется
                read_string(file, buffer, n);
            return;
        } 
        else 
        {
            buffer[i] = buf;
        }
    }
    buffer[n - 1] = '\0';
    if ((i == 1) && isspace(buf)) read_string(file, buffer, n);
}

int main(int argc, char **argv) 
{
    // проверка количества аргуметов камандной строки
    if (argc != 6)
    {
        printf("Incorect number of arguments\n");
        puts("Exemple: .\\main.exe file.txt -p 2 -n 5 ");
        exit(1);
    }

    char *buffer; 
    int p = 2, n = 5, page = 0, not_done = 1, written = 0; // p - количество строк на одной стронице, n - максимальная длина строки на страницу 
    FILE *file;
    file = fopen(argv[1], "r");
    
    //  проверка файла 
    if (file ==NULL)
    {
        puts("Invalid openning a file");
        puts("Exemple: .\\main.exe file.txt -p 2 -n 5");
        exit(1);
    }


// проверка опций -n и -p 
if (!(strcmp(argv[2],"-p") == 0 && atoi(argv[3])))
{
    puts("Invalid input of the -p option or its values\n\
    Exemple: .\\main.exe file.txt -p 2 -n 5");
    exit(1);
}
if (!(strcmp(argv[4],"-n") == 0 && atoi(argv[5])))
{
    puts("Invalid input of the -n option or its values\n\
    Exemple: .\\main.exe file.txt -p 2 -n 5");
    exit(1);
}

    // проверка агрументов командной строки 
    for (int i = 2; i <= argc-2; i++) 
    {
        if (!strcmp(argv[i], "-p"))
            p = atoi(argv[i+1]);
        if (!strcmp(argv[i], "-n")) 
            n = atoi(argv[i+1])+1;
    }
    if (p <= 0 || n <= 0) 
    {
    printf("Invalid arguments\n");
    exit(1);
    }

    // выделение памяти по буфер для чтения строк
    buffer = (char *)malloc(n * sizeof(char));
    if ((p == 0) || (n == 1)) 
    {  // проверка ввода 
        printf("— Page 1 —");
        return 0;
    }
    // цикл построчного вывода
    while (!feof(file)) 
    {
        written = 0;
        for (int i = 1; i <= p; i++)
        {
            read_string(file, buffer, n);
            if (strcmp(buffer, "")) 
            {
                printf("%d: %s\n", i, buffer);
                written = 1;
            } 
            else 
            {
                not_done = 0;
                break;
            }
        }
        if (written) printf("- Page %d -\n", ++page);
        if (!not_done) break;
    }
    // закрытие файла
    fclose(file);
    return 0;
}
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // zpracovani poctu parametru
    if (argc > 2)
    {
        fprintf(stderr, "Too many parameters!\n");
        return 1;
    } 
    else if (argc == 1)
    {
        printf("Whole list will be displayed!\n");
    }
    else
    {
        printf("Filtered list by: %s, will be displayed!\n", argv[1]);
    }    

    // pocet radku seznamu
    int c;
    int i = 0;
    int line = 1;
    char arra[101];
    while ((c = getchar()) != EOF)
    {
        while (c != 10)
        {
            i = 0;
            continue;
        }                                        
    }    
    printf("\n%d\n", line);    

    // cislo muze znamenat
    char *array[] = {
        "abc",
        "def",
        "ghi",
        "jkl",
        "mno",
        "pqrs",
        "tuv",
        "xyz"
    };
    printf("%c\n", array[0][0]);
}
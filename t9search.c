#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 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

#define TRUE 1
#define FALSE 0

void display_by_filter(char const *array)
{
    int i = 0;
    while (array[i] != 0)
    {
        printf("%c", array[i]);
        i++;
    }        
}

int main(int argc, char const *argv[])
{
    if (argc == 2)
    {
        printf("Contacts filtered by: \'%s\' should be displayed!\n", argv[1]);
        display_by_filter(argv[1]);
    }
    else
    {        
        printf("Too many parameters entered!\n");
        return 0;
    }    
    return 0;
}   
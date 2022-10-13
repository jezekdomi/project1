#include <stdio.h>

int main(int argc, char const *argv[])
{
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
        
    // load contacts from file and write them to stdout
    char c;
    int line = 0;

    while ((c = getchar()) != EOF)
    {              
        if (c == 10)
        {
            line++;
            printf(",");
        }
        printf("%c", c);
    }
    
    return 0;
}
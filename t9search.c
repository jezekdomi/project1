#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/* VARIABLES */

#define MAX_CONTACTS 42
#define MAX_LINE_LENGTH 100

typedef struct Contact
{
    char name[MAX_LINE_LENGTH];
    char phone[MAX_LINE_LENGTH];
} 
Contact;

Contact contact[MAX_CONTACTS];
int line;

/* --------- */

/* FUNCTIONS */

void read_stdin()
{
    char c;
    line = 1;
    char name_or_phone[MAX_LINE_LENGTH];

    while (!feof(stdin) && line / 2 <= MAX_CONTACTS)
    {
        for (int i = 0; i < MAX_LINE_LENGTH; i++)
        {
            // making sure that number is going to be number and name name, with its valid possibilities
            if ((((c = tolower(getchar())) == '.' || isalpha(c)) && (line % 2 == 1)) || isdigit(c) || c == ' ' || c == '\n' || c == '\r')
            {
                if (c == '.' || c == ' ' || isalnum(c))
                {
                    name_or_phone[i] = c;
                }
                else if (c != '\n')
                {
                    name_or_phone[i] = '\0';
                }
                else break;
            }
            else
            {
                fprintf(stderr, "Unexpected input data on line: %d!\n", line);
                exit(0);
            }
        }
        
        strcpy((line % 2) == 1 ? contact[line / 2].name : contact[line / 2 - 1].phone, name_or_phone);
        line++;
    }
}

/* --------- */

int main(int argc, char const *argv[])
{    
    read_stdin();
    
    printf("argc: %d, argv[1]: %s\n", argc, argv[1]);
    printf("%s, %s\n", contact[0].name, contact[0].phone);
    printf("%s, %s\n", contact[1].name, contact[1].phone);
}
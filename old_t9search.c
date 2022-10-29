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
    bool hidden;
} 
Contact;

const int options[10][5] = {
    {'0', '+'},
    {},
    {'2', 'a', 'b', 'c'},
    {'3', 'd', 'e', 'f'},
    {'4', 'g', 'h', 'i'},
    {'5', 'j', 'k', 'l'},
    {'6', 'm', 'n', 'o'},
    {'7', 'p', 'q', 'r', 's'},
    {'8', 't', 'u', 'v'},
    {'9', 'x', 'y', 'z'}
};

/* --------- */

/* FUNCTIONS */

void validate_args(const int number_of_args, const char *query);
void read_stdin(Contact *contact, int *num_of_contacts);
int matches_option(int query_key, int contact_key);
void query(Contact *contact, const int number_of_args, const char *query);
void print_contacts(Contact *contact, int num_of_contacts);

/* --------- */

int main(int argc, char const *argv[])
{    
    validate_args(argc, argv[1]);

    int num_of_contacts = 0;
    Contact contact[MAX_CONTACTS];

    read_stdin(contact, &num_of_contacts);

    query(contact, argc, argv[1]);
    print_contacts(contact, num_of_contacts);
}

void validate_args(const int number_of_args, const char *query)
{    
    if (number_of_args == 1)
    {
        return;
    }    
    else if (number_of_args == 2)
    {
        for (int i = 0; query[i] != '\0'; i++)
        {            
            if (!isdigit(query[i]))
            {
                fprintf(stderr, "Query contains invalid characters!\n");
                exit(0);
            }            
        }        
    }
    else
    {
        fprintf(stderr, "User passed too many arguments! (%d)\n", number_of_args);
        exit(0);
    }
}

void read_stdin(Contact *contact, int *num_of_contacts)
{
    int line;
    int c;

    c = tolower(getchar());

    if (c == EOF || c == '\n')
    {
        fprintf(stderr, "No data on stdin!\n");
        exit(0);
    }
    
    for (line = 1; c != EOF && line / 2 <= MAX_CONTACTS; line++)
    {
        for (int i = 0; (c = (i != 0 || line != 1) ? tolower(getchar()) : c) != '\n'; i++)
        {
            if (i > MAX_LINE_LENGTH)
            {
                fprintf(stderr, "Too long line on stdin!\n");
                exit(0);
            }
            
            // making sure that number is going to be number and name name, with its valid possibilities
            if (((c == '.' || isalpha(c)) && (line % 2 == 1)) || isdigit(c) || c == ' ' || c == '+' || c == '\n' || c == '\r' || c == EOF)
            {                
                if (c == '+' || c == '.' || c == ' ' || isalnum(c))
                {
                    if ((line % 2) == 1)
                    {
                        contact[line / 2].name[i] = c;
                    }
                    else
                    {
                        contact[line / 2 - 1].phone[i] = c;
                    }
                }
                else if (c == '\r')
                {
                    continue;
                }
                else break;
            }
            else
            {
                fprintf(stderr, "Unexpected input \'%c\' on line: %d!\n", c, line);
                exit(0);
            }
        }        
    }
    *num_of_contacts = line / 2;
}

int matches_option(int query_key, int contact_key)
{
    for (int i = 0; options[query_key - '0'][i] != '\0'; i++)
    {
        printf("match iteration: %d\n", i);
        if (options[query_key - '0'][i] == contact_key)
        {
            return 1;
        }
        i++;
    }
    return 0;
}

void query(Contact *contact, const int number_of_args, const char *query)
{
    if (number_of_args == 1)
    {
        return;
    }

    
    // zde uz zbyva jen nastavit u kontaktu hidden = true pokud u nej ani u jmena ani cisla nenajdeme shodu
}

void print_contacts(Contact *contact, int num_of_contacts)
{
    for (int i = 0; i < num_of_contacts; i++)
    {
        if (contact[i].hidden == false)
        {
            printf("%s, %s\n", contact[i].name, contact[i].phone);
        }        
    }    
}
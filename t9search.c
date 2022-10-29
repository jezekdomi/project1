#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define KEYS 10
#define MAX_OPTIONS 5
#define MAX_LINE_LENGTH 100
#define MAX_CONTACTS 42

const char keys[KEYS][MAX_OPTIONS] = {
    {'0', '+'},
    {},
    {'2', 'a', 'b', 'c'},
    {'3', 'd', 'e', 'f'},
    {'4', 'g', 'h', 'i'},
    {'5', 'j', 'k', 'l'},
    {'6', 'm', 'n', 'o'},
    {'7', 'p', 'q', 'r', 's'},
    {'8', 't', 'u', 'v'},
    {'9', 'w', 'x', 'y', 'z'}
};

typedef struct
{
    char name[MAX_LINE_LENGTH + 1];
    char phone[MAX_LINE_LENGTH + 1];
    bool hidden;
}
Contact;

/**
 * @param *contact Contact variable where to save data
 * @param is_line_odd Decide if line is odd or even
 * @return Returns FALSE on EOF
*/
bool check_save_line(Contact *contact, bool is_line_odd);

int main(int argc, char const *argv[])
{
    int contact_count;
    Contact contacts[MAX_CONTACTS];

    for (int line_on_turn = 1; line_on_turn < MAX_CONTACTS * 2 + 1; line_on_turn++)
    {
        int contact_on_turn = (line_on_turn - 1) / 2;
        bool is_line_odd = (line_on_turn % 2) == 1;

        if (!check_save_line(&contacts[contact_on_turn], is_line_odd))
        {
            break;
        }

        if ((line_on_turn % 2) == 0) contacts[contact_on_turn].hidden = true;

        contact_count = contact_on_turn + 1;
        printf("%d, %d, %d\n", is_line_odd, contact_on_turn, line_on_turn);
    }

    if (argc == 2)
    {
        for (int i = 0; i < contact_count; i++)
        {/*
            contacts[i].phone
            contacts[i].name
            contacts[i].hidden*/
        }
    }
    else if (argc != 1)
    {
        fprintf(stderr, "Some kind of error!");
        return EXIT_FAILURE;
    }

    // vypis kontaktuu

    return EXIT_SUCCESS;
}

bool check_save_line(Contact *contact, bool is_line_odd)
{
    int key;
    int i = 0;
    do
    {
        key = tolower(getchar());

        if (key == EOF) 
            return false;
                
        if (is_line_odd) // muze prijit cokoli, co nechceme
        {
            if (isalpha(key) || key == ' ' || key == '.')
            {
                contact->name[i] = key;
            }
            else if (key == '\r' || key == '\n')
            {
                contact->name[i] = '\0';
            }
            else exit(EXIT_FAILURE);
        }
        else
        {
            if (isdigit(key) || key == '+')
            {
                contact->phone[i] = key;
            }
            else if (key == '\r' || key == '\n')
            {
                contact->phone[i] = '\0';                
            }
            else exit(EXIT_FAILURE);         
        }        
        i++;

    } while (key != '\n');

    return true;
}
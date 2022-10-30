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
bool check_save_line(Contact *contact, bool is_line_odd, bool *found_invalid_value);

/**
 * @param query[] Query to count
 * @return Returns length of query
*/
int check_query_and_get_length(const char *query);

int main(int argc, char const *argv[])
{
    int contact_count;
    Contact contacts[MAX_CONTACTS];

    for (int line_on_turn = 1; line_on_turn < MAX_CONTACTS * 2 + 1; line_on_turn++)
    {
        int contact_on_turn = (line_on_turn - 1) / 2;
        bool is_line_odd = (line_on_turn % 2) == 1;
        bool found_invalid_value = false;

        if (!check_save_line(&contacts[contact_on_turn], is_line_odd, &found_invalid_value))
        {
            break;
        }

        if (found_invalid_value)
        {
            fprintf(stderr, "Invalid key found in phone number!");
            return 1;
        }
        
        if ((line_on_turn % 2) == 0) contacts[contact_on_turn].hidden = false;

        contact_count = contact_on_turn + 1;
        printf("%d, %d, %d\n", is_line_odd, contact_on_turn, line_on_turn);
    }

    if (argc == 2)
    {
        int query_length = check_query_and_get_length(argv[1]);

        if (query_length == 0)
        {
            fprintf(stderr, "Unexpected values on function call!\n");
            return 1;
        }        

        for (int i = 0; i < contact_count; i++)
        {
            /* CODE TO WRITE */

            // 
        }
    }
    else if (argc != 1)
    {
        fprintf(stderr, "Too many arguments on function call!\n");
        return 1;
    }

    int hidden_count = 0;
    for (int i = 0; i < contact_count; i++)
    {
        if (contacts[i].hidden == false)
        {
            printf("%s, %s\n", contacts[i].name, contacts[i].phone);
        }
        else
        {
            hidden_count++;
        }
    }

    if (hidden_count == contact_count)
    {
        printf("Not found!\n");
    }    

    return 0;
}

bool check_save_line(Contact *contact, bool is_line_odd, bool *found_invalid_value)
{
    int key;
    int i = 0;
    do
    {
        key = tolower(getchar());

        if (key == EOF)
        {
            return false;
        }
                
        if (is_line_odd)
        {
            if (key == '\r' || key == '\n')
            {
                contact->name[i] = '\0';
            }
            else
            {
                contact->name[i] = key;
            }
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
            else
            {
                *found_invalid_value = true;
                return true;
            }
        }        
        i++;

    } while (key != '\n');

    return true;
}

int check_query_and_get_length(const char *query)
{
    int i;
    for (i = 0; query[i] != '\0'; i++)
    {
        if (!isdigit(query[i]))
        {            
            return 0;
        }        
    }
    return ++i;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define KEYS 10
#define MAX_OPTIONS 6
#define MAX_LINE_LENGTH 100
#define MAX_CONTACTS 42

#define INVALID_KEY_ERROR "Invalid key found in phone number!\n"
#define UNEXPECTED_VALUES_ERROR "Unexpected values on function call!\n"
#define TOO_MANY_ARGS_ERROR "Too many arguments on function call!\n"
#define NOT_FOUND_ERROR "Not found!\n"

const char keys[KEYS][MAX_OPTIONS] = {
    {'0', '+', '\0'},
    {'1', '\0'},
    {'2', 'a', 'b', 'c', '\0'},
    {'3', 'd', 'e', 'f', '\0'},
    {'4', 'g', 'h', 'i', '\0'},
    {'5', 'j', 'k', 'l', '\0'},
    {'6', 'm', 'n', 'o', '\0'},
    {'7', 'p', 'q', 'r', 's', '\0'},
    {'8', 't', 'u', 'v', '\0'},
    {'9', 'w', 'x', 'y', 'z', '\0'}
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

/**
 * @param *object Object to compare query to
 * @param *contact Object's parent
 * @return Returns TRUE when contact matches query
*/
bool query(char *object, Contact *contact, const char *query, int query_length);

/**
 * @return Returns TRUE when key from contact matches its option
 * @param contact_key Key from contact atribute
 * @param char_key Key from query
*/
bool key_matches_option(char contact_key, char query_key);

int main(int argc, char const *argv[])
{
    int contact_count;
    Contact contacts[MAX_CONTACTS];

    for (int line_on_turn = 1; line_on_turn < MAX_CONTACTS * 2; line_on_turn++)
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
            fprintf(stderr, INVALID_KEY_ERROR);
            return 1;
        }
        
        if ((line_on_turn % 2) == 0) contacts[contact_on_turn].hidden = false;

        contact_count = contact_on_turn + 1;
    }

    if (argc == 2)
    {
        int query_length = check_query_and_get_length(argv[1]);

        if (query_length == 0)
        {
            fprintf(stderr, UNEXPECTED_VALUES_ERROR);
            return 1;
        }        

        for (int i = 0; i < contact_count; i++)
        {       
            if (!query(contacts[i].phone, &contacts[i], argv[1], query_length))
            {
                query(contacts[i].name, &contacts[i], argv[1], query_length);
            }
        }
    }
    else if (argc != 1)
    {
        fprintf(stderr, TOO_MANY_ARGS_ERROR);
        return 1;
    }

    int hidden_contacts_count = 0;
    for (int i = 0; i < contact_count; i++)
    {
        if (contacts[i].hidden == false)
        {
            printf("%s, %s\n", contacts[i].name, contacts[i].phone);
        }
        else
        {
            hidden_contacts_count++;
        }
    }

    if (hidden_contacts_count == contact_count)
    {
        fprintf(stderr, NOT_FOUND_ERROR);
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
    return i;
}

bool query(char *object, Contact *contact, const char *query, int query_length)
{
    for (int i = 0; object[i] != '\0'; i++)
    {
        int match_count = 0;

        for (int j = 0; j < query_length; j++)
        {
            if (object[i + j] == '\0')
            {
                contact->hidden = true;
                return false;
            }

            if (key_matches_option(object[i + j], query[j]))
            {
                match_count++;
            }
        }

        if (match_count == query_length)
        {
            contact->hidden = false;
            return true;
        }
        else
        {
            contact->hidden = true;
        }
    }
    
    return false;
}

bool key_matches_option(char object_key, char query_key)
{
    int option;
    int anchor = '0';
    int position = query_key - anchor;

    for (int i = 0; keys[position][i] != '\0'; i++)
    {
        position = query_key - anchor;
        option = keys[position][i];

        if (option == object_key)
        {
            return true;
        }
    }    
    
    return false;
}
#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct Contact
{
    char name[100]; 
    char phone[100];    
};

const int keyboard[9][5] = {
    {'0', '+'},
    {'2', 'a', 'b', 'c'},
    {'3', 'd', 'e', 'f'},
    {'4', 'g', 'h', 'i'},
    {'5', 'j', 'k', 'l'},
    {'6', 'm', 'n', 'o'},
    {'7', 'p', 'q', 'r', 's'},
    {'8', 't', 'u', 'v'},
    {'9', 'x', 'y', 'z'}
};

int main(int argc, char const *argv[])
{    
    if (argc > 2)
    {
        fprintf(stderr, "Too many arguments!\n");
        return 1;
    }
    else if (argc == 1)
    {
        printf("Whole list be displayed!\n");
    }    
    else
    {
        printf("List filtered by: %s, shall be displayed!\n", argv[1]);
    }
    
    int c;
    if ((c = getchar()) == EOF)
    {
        fprintf(stderr, "No contacts found!\n");
        return 1;
    }

    // cti radek a zapis ho do struct kontakt
    unsigned current_line = 1;
    char line[100];
    int i_contact;
    struct Contact contact[42];
    do
    {        
        int i = 0;
        do {
            line[i] = tolower(c);
            i++;
        } 
        while ((c = getchar()) != '\r' && c != EOF && i < 100);
        line[i] = '\0';

        i_contact = current_line % 2 == 1 ? current_line / 2 : current_line / 2 - 1;
        strcpy(current_line % 2 == 1 ? contact[i_contact].name : contact[i_contact].phone, line);
        
        c = getchar(); // flush '\n' from stdin
        current_line++;

        // if (current_line % 2 == 0) printf("%s, %s\n", contact[i_contact].name, contact[i_contact].phone);
    }    
    while ((c = getchar()) != EOF && current_line <= 84);
    
    int contacts_count = i_contact + 1;
    i_contact = 0;
    while (i_contact < contacts_count)
    {
        int num_match_count = 0;
        int i_prev_matched = -1;
        int i_char_in_phone;
        int i_query = 0;

        // loop pro cislo ve filtru
        while (i_query < strlen(argv[1]))
        {
            i_char_in_phone = i_prev_matched + 1;

            // loop pro cislo v telefonnim cisle
            while (argv[1][i_query] != contact[i_contact].phone[i_char_in_phone] && contact[i_contact].phone[i_char_in_phone] != '\0')
            {
                i_char_in_phone++;
            }

            // shoda ve znaku
            if (argv[1][i_query] == contact[i_contact].phone[i_char_in_phone] && i_prev_matched < i_char_in_phone)
            {
                i_prev_matched = i_char_in_phone;
                num_match_count++;
            }            
            i_query++;

            // pri match a konci filtru -> ulozeni kontaktu
            if (i_query == num_match_count && i_query == strlen(argv[1]))
            {
                printf("%s, %s\n", contact[i_contact].name, contact[i_contact].phone);
            }
        }        

        // int i_char_in_phone_number;

        // // loop pro cislo ve filtru
        // while (i_query < strlen(argv[1]))
        // {
        //     i_char_in_phone_number = i_found_phone_number_char + 1;

        //     // loop pro cislo ve jmene
        //     while (argv[1][i_query] != contact[i_contact].phone[i_char_in_phone_number] && contact[i_contact].phone[i_char_in_phone_number] != '\0')
        //     {
        //         i_char_in_phone_number++;
        //     }            

        //     // shoda ve znaku
        //     if (argv[1][i_query] == contact[i_contact].phone[i_char_in_phone_number] && i_found_phone_number_char < i_char_in_phone_number) {
        //         i_found_phone_number_char = i_char_in_phone_number;
        //         phone_number_chars_match_count++;
        //     }            
        //     i_query++;

        //     // pri match a konci filtru -> ulozeni kontaktu
        //     if (i_query == phone_number_chars_match_count && i_query == strlen(argv[1])) {
        //         printf("%s, %s\n", contact[i_contact].name, contact[i_contact].phone);
        //     }
        // }
        i_contact++;        
    }
}
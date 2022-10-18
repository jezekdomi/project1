#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct Contact
{
    char name[100]; 
    char phone[100];    
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
        do
        {
            line[i] = tolower(c);
            i++;
        } 
        while ((c = getchar()) != '\r' && c != EOF && i < 100);
        line[i] = '\0';

        i_contact = current_line % 2 == 1 ? current_line / 2 : current_line / 2 - 1;
        strcpy(current_line % 2 == 1 ? contact[i_contact].name : contact[i_contact].phone, line);
        
        // spotreba zbytecneho znaku '\n' na stdin
        c = getchar();
        current_line++;

        // if (current_line % 2 == 0) printf("%s, %s\n", contact[i_contact].name, contact[i_contact].phone);
    }    
    while ((c = getchar()) != EOF && current_line <= 84);
            
    int contacts_count = i_contact + 1;
    i_contact = 0;

    // nalezeni cisla s prerusenou posloupnosti odpovidajici filtru
    while (i_contact < contacts_count)
    {
        int chars_match_count = 0;        
        int i_found_phone_number = -1;   
        int i_query = 0;

        // loop pro cislo ve filtru
        while (argv[1][i_query] != '\0' && i_query < strlen(argv[1]))
        {
            int i_char_in_phone_number = i_found_phone_number + 1;

            // loop pro cislo v telefonnim cisle
            while (argv[1][i_query] != contact[i_contact].phone[i_char_in_phone_number] && contact[i_contact].phone[i_char_in_phone_number] != '\0')
            {
                i_char_in_phone_number++;
            }

            // shoda ve znaku
            if (argv[1][i_query] == contact[i_contact].phone[i_char_in_phone_number] && i_found_phone_number < i_char_in_phone_number) {
                i_found_phone_number = i_char_in_phone_number;
                chars_match_count++;
            }            
            i_query++;

            // pri match a konci filtru -> ulozeni kontaktu
            if (i_query == chars_match_count && i_query == strlen(argv[1])) {
                printf("%s, %s\n", contact[i_contact].name, contact[i_contact].phone);
            }
        }        
        i_contact++;        
    }
}
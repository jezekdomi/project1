#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct Kontakt
{
    char jmeno[100]; 
    char telefon[100];    
};

int main(int argc, char const *argv[])
{
    // zpracovani poctu zadanych argumentu
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
    
    // jsou k dispozici nejake kontakty?
    int c;    
    if ((c = getchar()) == EOF)
    {
        fprintf(stderr, "No contacts found!\n");
        return 1;
    }

    // cti radek a zapis ho do struct kontakt
    int ctenyRadek = 1;
    char prectenyRadek[100];
    int poradiKontaktu;
    struct Kontakt kontakt[42];

    do
    {        
        int i = 0;
        do
        {
            prectenyRadek[i] = tolower(c);
            i++;
        } 
        while ((c = getchar()) != '\r' && c != EOF && i < 100);
        prectenyRadek[i] = '\0';

        // prirazeni radku do kontaktu
        poradiKontaktu = ctenyRadek % 2 == 1 ? ctenyRadek / 2 : ctenyRadek / 2 - 1;
        
        strcpy(ctenyRadek % 2 == 1 ? kontakt[poradiKontaktu].jmeno : kontakt[poradiKontaktu].telefon, prectenyRadek);
        // if (ctenyRadek % 2 == 0) printf("%s, %s\n", kontakt[poradiKontaktu].jmeno, kontakt[poradiKontaktu].telefon);            
        
        // spotreba zbytecneho znaku '\n' na stdin
        c = getchar();
        ctenyRadek++;
    }    
    while ((c = getchar()) != EOF && ctenyRadek <= 84);
        
    int kontaktNaRade = 0;
    int pocetKontaktu = poradiKontaktu + 1;
    // nalezeni cisla s prerusenou posloupnosti odpovidajici filtru
    // pocet iteraci podle poctu kontaktu
    // loop pro kontakt na rade
    while (kontaktNaRade < pocetKontaktu)
    {
        int shoda = 0;        
        int indexNalezeneho = -1;   
        int cisloNaRadeVeFiltru = 0;
        // loop pro cislo ve filtru
        while (argv[1][cisloNaRadeVeFiltru] != '\0' && cisloNaRadeVeFiltru < strlen(argv[1]))
        {
            int cisloNaRadeVTelefonu = indexNalezeneho + 1;
            // loop pro cislo v telefonnim cisle
            // pokud se cislo filtru shoduje s cislem v telefonnim cisle
            // a ma vyssi index nez predchozi nalezene, tak prejdeme na dalsi cislo ve filtru
            while (argv[1][cisloNaRadeVeFiltru] != kontakt[kontaktNaRade].telefon[cisloNaRadeVTelefonu] && 
                kontakt[kontaktNaRade].telefon[cisloNaRadeVTelefonu] != '\0')
            {
                cisloNaRadeVTelefonu++;
            }

            // pokud mame match cisla a index nasledujiciho je vetsi nez predtim, dame match++
            if (argv[1][cisloNaRadeVeFiltru] == kontakt[kontaktNaRade].telefon[cisloNaRadeVTelefonu]
                && indexNalezeneho < cisloNaRadeVTelefonu)
            {
                indexNalezeneho = cisloNaRadeVTelefonu;
                shoda++;
            }            
            cisloNaRadeVeFiltru++;

            if (cisloNaRadeVeFiltru == shoda && cisloNaRadeVeFiltru == strlen(argv[1]))
            {
                printf("%s, %s\n", kontakt[kontaktNaRade].jmeno, kontakt[kontaktNaRade].telefon);
                // printf("Match in phone number on %d. contact\n", kontaktNaRade + 1);
            }
        }        
        kontaktNaRade++;        
    }    
}
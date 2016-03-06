#include <stdio.h>

int main (void) {

    int c;
    int anzahlZeichen = 0;
    int wortZwischenRaeume = 0;
    int anzahlWörter = 0;

//for every char read anzhalZeichen is incremented until return is pressed
    (void)printf("Type your text and after pressing return it will be counted.\n");
        while( (c = getchar()) !='\n') {
        if ((c == ' ') || (c == '\t')) {
            wortZwischenRaeume++;
        }
        anzahlZeichen++;
    }
//prints out the charcount
    (void)printf(" -->Anzahl Zeichen im Satz: %d \n",anzahlZeichen-wortZwischenRaeume);
    (void)printf(" -->Anzahl Wörter im Satz: %d \n",anzahlWörter);
}
#include <stdio.h>
#include <ctype.h>
int c;
int previousChar;
int anzahlZeichen = 0;
int anzahlWörter = 1;

int isSpaceOrTab(int s){
    if(s == ' ' || s == '\t') {
        return 1;
    }
    else {
        return 0;
    }
};

void countSpace () {
    while ((c = getchar()) !='\n') {
        if (isSpaceOrTab(c) && !isSpaceOrTab(previousChar) ) {
            anzahlWörter++;
        }
        if(isSpaceOrTab(c)){
            anzahlZeichen--;
        }
        anzahlZeichen++;
        previousChar = c;
    }
}



int main (void) {

//for every char read anzhalZeichen is incremented until return is pressed
    (void)printf("Type your text and after pressing return it will be counted.\n");
    countSpace();
//prints out the charcount
    (void)printf("+%d Wörter, %d Zeichen \n",anzahlWörter,anzahlZeichen);
}

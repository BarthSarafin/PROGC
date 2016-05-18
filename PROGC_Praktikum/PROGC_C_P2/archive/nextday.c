/* nextday.c
   Autor: Marc Rennhard, urspruenglich Peter Frueh
   Datum: 2.4.2007

   Liest ein Datum ein und gibt - falls das Datum gueltig ist -
   das Datum des folgenden Tages aus.
*/


#include <stdio.h>

/* Monatsnamen und struct fuer ein Datum */
enum {Jan=1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec};

typedef struct {
    int day;
    int month;
    int year;
} Date;

/* Funktionsdeklarationen */
int daysInMonth(Date currentDate);
int legalDate (Date currentDate);
Date getTomorrow (Date currentDate);

/* daysInMonth nimmt ein Datum vom Datentyp Date als Parameter
   und gibt die Anzahl Tage des Monats zurueck */
int daysInMonth(Date currentDate) {
    switch (currentDate.month) {
        case Apr: case Jun: case Sep: case Nov:
            return 30;
        case Feb:

            /* Ein Schaltjahr ist ein Jahr, das durch 4 aber nicht durch 100
               teilbar ist. Ist das Jahr aber durch 400 teilbar, dann ist es
               immer ein Schaltjahr */
            if (((currentDate.year % 4) == 0) &&
                ((currentDate.year % 100) != 0) ||
                ((currentDate.year % 400) == 0)) {
                return 29;
            } else {
                return 28;
            }
        default:
            return 31;
    }
}

/* legalDate kontrolliert ob das spezifizerte Datum ein gueltiges
   Datum ist. Ist das Datum gueltig, wird 1 zurueckgegeben, sonst 0 */
int legalDate (Date currentDate) {
    if (currentDate.year < 0) {
        return 0;
    } else if ((currentDate.month < Jan) || (currentDate.month > Dec)) {
        return 0;
    } else if ((currentDate.day < 1) || (currentDate.day > daysInMonth(currentDate))) {
        return 0;
    }
    return 1;
}

/* getTomorrow nimmt ein existierendes Datum als Input und gibt
   das Datum des folgenden Tags zurueck */
Date getTomorrow (Date currentDate) {
    Date nextDate = currentDate;

    if (currentDate.day != daysInMonth(currentDate)) {
        nextDate.day++;
    } else {
        nextDate.day = 1;
        if (currentDate.month != Dec) {
            nextDate.month++;
        } else {
            nextDate.month = Jan;
            nextDate.year++;
        };
    }
    return nextDate;
}

/* Hauptprogramm */
int main (void) {
    Date currentDate, nextDate;
    int cont = 1;
    char answer;

    /* Programm laeuft solange, bis der Benutzer abbricht */
    while (cont) {

        /* Benutzer soll Datum eingeben */
        printf("Enter day month and year (e.g. 24 12 2003) and press enter: ");
        fflush(stdout);
        scanf("%d%d%d", &currentDate.day, &currentDate.month,
              &currentDate.year);
        getchar();  /* This is needed to absorb the newline character
                   that completed entering a date; otherwise this
                   character will be read below */

        /* Kontrolle, ob gueltiges Datum */
        if (legalDate(currentDate)) {
            nextDate = getTomorrow(currentDate);
            printf("Entered date: %d.%d.%d", currentDate.day,
                   currentDate.month, currentDate.year);
            printf(" -> next day: %d.%d.%d\n", nextDate.day,
                   nextDate.month, nextDate.year);
        } else {
            printf("Entered date is not valid\n", currentDate.day,
                   currentDate.month, currentDate.year);
        }
        printf("Continue (y/n)? ");
        scanf("%c", &answer);
        cont = (answer == 'Y') || (answer == 'y');
    }
}

/* marks.c
   Created by BarthSarafin on 12/04/2016.

   Liest eine Serie von Punktzahlen in einen Array ein und
   liefert - abhaengig von der Punktzahl, die fuer eine
   6 notwendig ist, die Notenstatistik.
*/


#include <stdio.h>
#include <math.h>

#define MAX 100

/* Struktur fuer die Notenstatistik */
typedef struct {
    int marks[6];
    int best;
    int worst;
    double average;
    int atLeast4;
} Statistics;

/* Funktionsdeklarationen */
Statistics getStatistics(int points[], int len, int minPoints6);
int getMark(int points, int minPoints6);

/* getStatistics generiert die Notenstatistik zu einem Array points[]
   mit len Noten, wobei minPoints6 die minimal benoetigte Punktzahl
   fuer eine 6 ist */
Statistics getStatistics(int points[], int len, int minPoints6) {
    Statistics stat;
    int i;
    int mark;

    /* Zuerst werden die den Punktzahlen entsprechenden Noten
       generiert und gezaehlt */
    for (i = 0; i < 6; i++) {
        stat.marks[i] = 0;
    }
    for (i = 0; i < len; i++) {
        mark = getMark(points[i], minPoints6);
        stat.marks[mark -1]++;
    }

    /* Jetzt wird der Rest der Statistik erstellt */
    stat.best = 1;
    stat.worst = 6;
    stat.average = 0;
    stat.atLeast4 = 0;
    for (i = 0; i < 6; i++) {
        stat.average += (i + 1) * stat.marks[i];
        if (stat.marks[i] > 0) {
            if ((i + 1) < stat.worst) {
                stat.worst = i + 1;
            }
            if ((i + 1) > stat.best) {
                stat.best = i + 1;
            }
        }
        if (i >= 3) {
            stat.atLeast4 += stat.marks[i];
        }
    }
    stat.average = stat.average / len;
    return stat;
}

/* getMark berechnet die Note, welche mit points Punkten erzielt
   wird, wobei minPoints6 die minimal benoetigte Punktzahl
   fuer eine 6 ist */
int getMark(int points, int minPoints6) {
    double mark;

    /* Formel fuer Notenberechnung: lineare Verteilung zwischen
       1 und 6, .5 oder mehr wird aufgerundet */
    mark = 5.0 * points / minPoints6 + 1;
    if ((mark - (int) mark) >= 0.5) {
        mark = ceil(mark);
    } else {
        mark = floor(mark);
    }
    if (mark > 6) {
        mark = 6;
    }
    return (int) mark;
}

/* Hauptprogramm */
int main(void) {
    int points[MAX];
    int pt;
    int students = 0;
    int cont = 1;
    int i;
    char answer;
    Statistics stat;

    /* Eingabe der Noten, Beenden mit -1 */
    while(cont) {
        printf("Insert points of student (or -1): ");
        scanf("%d", &pt);
        if (pt >= 0) {
            points[students++] = pt;
        } else if (pt == -1) {
            if (students == 0) {
                printf("You must enter the marks of at least 1 student\n");
            } else {
                cont = 0;
            }
        } else {
            printf("Invalid entry\n");
        }
    }

    /* Berechnen der Notenstatistik, bis Benutzer abbricht */
    cont = 1;
    while (cont) {
        printf("Enter required points for 6: ");
        scanf("%d", &pt);
        getchar();
        stat = getStatistics(points, students, pt);

        /* Print statistics */
        printf("-------------------------------------------------------\n");
        printf("Statistics (%d students, %d points needed for mark 6):\n\n",
               students, pt);
        for (i = 5; i >= 0; i--) {
            printf("  Mark %d: %d\n", (i + 1), stat.marks[i]);
        }
        printf("\n  Best mark:    %d\n  Worst mark:   %d\n",
               stat.best, stat.worst);
        printf("  Average mark: %.2f\n  Mark >= 4:    %d students (%.2f %%)\n", stat.average,
               stat.atLeast4, (double) 100 * stat.atLeast4 / students);
        printf("-------------------------------------------------------\n");
        printf("Do you want to specify another required points for 6 (y/n)? ");
        scanf("%c", &answer);
        cont = (answer == 'Y') || (answer == 'y');
    }
}


/* count.c
   Created by BarthSarafin on 22/02/2016.

   Zaehlt die Zeichen und die Woerter einer mit \n abgeschlossenen
   Zeile. Als Wortzwischenraeume zählen Leerzeichen (' ') und
   Tabs ('\t').

   Hinweis zu getchar: Wie alle Funktionen auf Streams (stdin,
   stdout und stderr sind Streams) kehrt ein Aufruf von getchar
   nicht sofort zurueck, sondern puffert Zeichen bis ein '\n'
   von stdin gelesen wird. Sobald dieses '\n' eingegeben wird,
   wird getchar jeweils direkt nach dem Aufruf zurueckkehren und
   das naechste Zeichen im Buffer liefern, bis der Buffer leer ist.
   Dann blockiert der Aufruf von getchar wieder.
*/


# include <stdio.h>

#define IN  1  /* Zustand: innerhalb eines Wortes */
#define OUT 2  /* Zustand: ausserhalb eines Wortes */

int main(void) {
    int chars = 0;
    int words = 0;
    char c;
    int state = OUT;  /* Am Anfang ist man ausserhalb eines Wortes */

    while ((c = getchar()) != '\n') {
        chars++;
        if (c == ' ' || c == '\t') {

            /* Ein white-space Zeichen ist eingegeben worden, danach ist man
               ausserhalb eines Wortes */
            state = OUT;
        } else {

            /* Ein anderes Zeichen ist aufgetreten; wenn man sich noch nicht
               innerhalb eines Wortes befindet, dann ist dies der Beginn eines
               neuen Wortes */
            if (state == OUT) {
                words++;
                state = IN;
            }
        }
    }
    printf("%d Zeichen; %d Woerter\n", chars, words);
}

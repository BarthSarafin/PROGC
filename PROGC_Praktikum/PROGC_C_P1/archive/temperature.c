/* temperatur.c
   Created by BarthSarafin on 22/02/2016.

   Berechnet die Temperatur in Celsius fuer Fahrenheit-Werte von
   -100 bis +200 Grad, in 20er Schritten.
*/


# include <stdio.h>

int main(void) {
    int fahr;
    double celsius;

    printf("F'heit    Celsius\n");
    printf("-----------------\n");

    for (fahr = -100; fahr <= 200; fahr += 20) {
        celsius = 5.0/9.0 * (fahr - 32);
        printf("%6d    %7.2f\n", fahr, celsius);
    }
}


#include <stdio.h>



int main(void) {

    int startFahrenheit;
    int endFahrenheit = 200;
    float celsius;

    (void)printf("F'heit    Celsius\n_ _ _ _ _ _ _ _ _ \n");

    for(startFahrenheit = -100; startFahrenheit <= endFahrenheit; startFahrenheit += 20) {
        celsius = (double) 5/9*(startFahrenheit-32);
        (void)printf("\n%5i    %5.2f",startFahrenheit,celsius);
    }

}
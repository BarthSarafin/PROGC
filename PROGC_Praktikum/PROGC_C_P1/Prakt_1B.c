#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main () {

    double d;
    typedef struct {
        double x;
        double y;
    } Point2D;

    Point2D p1;
    Point2D p2;

    (void)printf("Enter Values for p1(X)\n");
        scanf("%f",&p1.x);
    (void)printf("Enter Values for p1(Y)\n");
        scanf("%f",&p1.y);
    (void)printf("Enter Values for p2(X)\n");
        scanf("%f",&p2.x);
    (void)printf("Enter Values for p2(Y)\n");
        scanf("%f",&p2.y);


    d = sqrt(pow((p1.x - p2.x),2)+pow((p2.y - p2.y),2));
    (void)printf("Distanz zwischen p1 und p2 beträgt: %f \n",d);

    (void)printf("p1.x= %f \n",p1.x);
    (void)printf("p1.x= %f \n",p1.y);
    (void)printf("p1.x= %f \n",p2.x);
    (void)printf("p1.x= %f \n",p2.y);

}

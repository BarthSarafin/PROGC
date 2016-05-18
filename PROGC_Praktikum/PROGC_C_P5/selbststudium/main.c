/*  main.c
    Created by BarthSarafin on 18/04/2016.

    person administration application.
    */

#include <stdio.h>
#include "person.h"
#include "list.h"
#include "list.c"
#include "person.c"

int main (char** argv) {
    Person p;
    ListElement l;
    char action = 'x';
    char c;
    int rounds, i;

    init(&l);

    while ((action != 'E') && (action != 'e')) {
        printf("I(insert), R(emove), S(how), C(lear), E(nd): ");
        action = (char)getchar();
        getchar();
        switch (action) {
            case 'I': case 'i':
                printf("Enter name, first name and age: ");
                scanf("%s%s%d", p.name, p.firstname, &p.age);
                getchar();
                insertPers(&l, &p);
                break;
            case 'R': case 'r':
                printf("Enter name, first name and age: ");
                scanf("%s%s%d", p.name, p.firstname, &p.age);
                getchar();
                if (!removePers(&l, &p)) {
                    printf("No such person\n");
                }
                break;
            case 'S': case 's':
                show(&l);
                break;
            case 'C': case 'c':
                clear(&l);
                break;
            case 'E': case 'e':
                break;
            default:
                printf("Illegal operation\n");
        }
    }
}
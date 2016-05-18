/*  person.c
    Created by BarthSarafin on 18/04/2016.

    Implements a person. There are some functions one can do on a person, such as comparing two persons.
    Name and age are compared.
    */

#include <string.h>
#include "person.h"

/* persCmp compares to persons alphabetically, first the name, then the surname.
   Are they the same the age will be the deciding factor.
   If person 1 < person 2 then -1 will be returned. Is it the other way around is 1 returned.
   For the case of a tie, 0 will be returned.*/
int persCmp(const Person* p1, const Person* p2) {
    int str;

    str = strcmp(p1->name, p2->name);
    if (str < 0) {
        return -1;
    } else if (str > 0) {
        return 1;
    } else {

        /* the names are the same, firstnames are compared */
        str = strcmp(p1->firstname, p2->firstname);
        if (str < 0) {
            return -1;
        } else if (str > 0) {
            return 1;
        } else {

            /* age comparison for same names, firstnames */
            if (p1->age < p2->age) {
                return -1;
            } else if (p1->age > p2->age) {
                return 1;
            } else {
                return 0;
            }
        }
    }
}


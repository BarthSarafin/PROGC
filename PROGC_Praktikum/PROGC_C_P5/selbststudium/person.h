/*  person.h
    Created by BarthSarafin on 18/04/2016.
    */

#ifndef PROGC_BACHMSTE_GREUTNIC_PERSON_H
#define PROGC_BACHMSTE_GREUTNIC_PERSON_H

/* a person */
typedef struct {
    char name[20];
    char firstname[20];
    unsigned age;
} Person;

/* Compare function on person. Pointers to the structure are parameters */
int persCmp(const Person* p1, const Person* p2);

#endif //PROGC_BACHMSTE_GREUTNIC_PERSON_H

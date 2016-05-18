/*  list.h
    Created by BarthSarafin on 18/04/2016.
    Header for listoperations of list.c
    */

#ifndef PROGC_BACHMSTE_GREUTNIC_LIST_H
#define PROGC_BACHMSTE_GREUTNIC_LIST_H

#include "person.h"

/* element in the list */
typedef struct LE {
    Person content;
    struct LE *next;
} ListElement;

/* functions on the list */
void init(ListElement* l);
void insertPers(ListElement* l, const Person* p);
int removePers(ListElement* l, const Person* p);
void show(const ListElement* l);
void clear(ListElement* l);

#endif //PROGC_BACHMSTE_GREUTNIC_LIST_H

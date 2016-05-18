/*  list.c
    Created by BarthSarafin on 18/04/2016.

    implementation of the linked list. contains persons.
    */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "person.h"

/* Initialising list with selfpointing element */
void init(ListElement* l) {
    l->next = l;
}

/* adds an element in alphabetical order */
void insertPers(ListElement* l, const Person* p) {
    ListElement *nl = (ListElement*) malloc(sizeof(ListElement));
    ListElement *temp = l;
    nl->content = *p;
    while ((temp->next != l) && (persCmp(&(temp->next->content), p) < 0)) {
        temp = temp->next;
    }
    nl->next = temp->next;
    temp->next = nl;
}

/* removes an element of the list */
int removePers(ListElement* l, const Person* p) {
    ListElement *temp = l;
    while ((temp->next != l) && (persCmp(&(temp->next->content), p) < 0)) {
        temp = temp->next;
    }
    if (persCmp(&(temp->next->content), p) == 0) {
        ListElement *rem = temp->next;
        temp->next = temp->next->next;
        free(rem);
        return 1;
    } else {
        return 0;
    }
}

/* prints out the list in alphabetical order */
void show (const ListElement* l) {
    const ListElement *temp = l;
    while (temp->next != l) {
        printf("%s, %s (%d)\n", temp->next->content.name,
               temp->next->content.firstname,
               temp->next->content.age);
        temp = temp->next;
    }
}

/* purges the list of all elements */
void clear (ListElement* l) {
    ListElement *temp = l->next;
    while (temp != l) {
        ListElement *rem = temp;
        temp = temp->next;
        free(rem);
    }
    init(l);
}
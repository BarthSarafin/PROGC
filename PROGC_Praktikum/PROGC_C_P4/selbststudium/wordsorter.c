//
// Created by BarthSarafin on 17/04/2016.
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wordsorter.h"

void enterString(void){
    int enterstring = 1;
    while(enterstring) {
        (void) printf("Please enter a string with no more than 20 characters.\n");
        (void) scanf("%s", word);

        length = sizeof(word);

        char *aString;
        aString = (char *) malloc(length);
        strcpy(aString, word);

        wordlist[position] = aString;
        position++;


        (void) printf("Next String? [0/1]?\n");
        (void) scanf("%d", &enterstring);
        fflush(stdin);
    }
    return;
}

void swap(char *a, char *b){
    char temporary;

    temporary = *a;
    *a = *b;
    *b = temporary;
}

void sortString(char *begin, char *end){
    char *ptr;
    char *split;
    if (end - begin <= 1)
        return;
    ptr = begin;
    split = begin + 1;
    while (strcmp(++ptr,end) >= 0) {
        if (strcmp(ptr,begin) < 0) {
            swap(ptr, split);
            ++split;
        }
    }
    swap(begin, split - 1);
    sortString(begin, split - 1);
    sortString(split, end);
    (void)printf("Array has been sorted");
}

int cmpfunc(const void *a, const void *b) {
    int return_value;
    const char **aplus = (const char **)a;
    const char **bplus = (const char **)b;

    if(!*aplus){
        return_value = 1;
    }else if(!*bplus){
        return_value = -1;
    }else {
        return_value = strcmp(*aplus, *bplus);
    }
    return return_value;
}

void sortThatString(size_t stringLength) {
    qsort(wordlist,stringLength,sizeof(char *), cmpfunc);
    (void)printf("Array has been sorted\n");
}


void printString(char **wordlist, size_t n){
    size_t i;
    (void) printf("Your Strings are:\n");
    for (i = 0; i < n; ++i) {
        if(wordlist[i] != NULL) {
            (void) printf("%s \n", wordlist[i]);
        }
    }
    return;
}
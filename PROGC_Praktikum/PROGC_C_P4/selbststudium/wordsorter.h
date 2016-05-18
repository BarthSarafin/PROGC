//
// Created by BarthSarafin on 17/05/2016.
//

#ifndef PROGC_BACHMSTE_GREUTNIC_WORDSORTER_H
#define PROGC_BACHMSTE_GREUTNIC_WORDSORTER_H

#define WORDLENGTH 20
#define WORDAMOUNT 100

static char word[WORDLENGTH];
static char* wordlist[WORDAMOUNT];
size_t length;
int position;

void enterString(void);
void swap(char *a, char *b);
void sortString(char *begin, char *end);
int cmpfunc(const void *a, const void *b);
void sortThatString(size_t stringLength);
void printString(char **array, size_t n);

#endif //PROGC_BACHMSTE_GREUTNIC_WORDSORTER_H

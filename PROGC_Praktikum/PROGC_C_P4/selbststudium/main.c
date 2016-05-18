//
// Created by BarthSarafin on 17/05/2016.
//

#include <stdio.h>
#include "wordsorter.h"
#include "wordsorter.c"

void main (){
    int choice;
    char option = "Y";
    size_t n = sizeof(wordlist) / sizeof(char *);
    position = 0;

    printf("STRING SORTING AVAILABLE\n");
    while(option = "Y"){
        (void) printf("---------------------------------\n");
        (void) printf("         1 ----->   ENTER STRING \n");
        (void) printf("         2 ----->   SORT STRINGS \n");
        (void) printf("         3 ----->   PRINT        \n");
        (void) printf("         4 ----->   QUIT!        \n");
        (void) printf("---------------------------------\n");

        (void) printf("Please enter your choice to proceed!\n");
        (void) scanf("%d", &choice);
        switch (choice){
            case 1:
                enterString();
                break;
            case 2:
                sortThatString(n);
                break;
            case 3:
                printString(wordlist,n);
                break;
            case 4:
                (void) printf("Goodbye!");
                return;
            default:
                printString(wordlist,n);
        }
        (void) printf("Would you like to continue? [Y/N]?\n");
        (void) scanf("%c", &option);
        fflush(stdin);
    }
    (void) printf("Goodbye!");
}
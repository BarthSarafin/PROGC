/*
  Created by BarthSarafin on 18/05/2016.


   Liest Wörter von der Tastatur ein und gibt - nachdem das Ende
   der Eingabe mit "ZZZ" spezifiziert wurde - die Wörter
   alphabetisch sortiert aus.

   Hinweis: Überall, wo ein Funktionsparameter mit char**
   spezifiziert wurde, könnte man auch char* [] verwenden. Statt
   char** wordlist geht zB also char* wordlist[]. Dies funktioniert,
   weil der Compiler die Array-Schreibweise sowieso in die Pointer-
   schreibweise umwandelt.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define size 100

/* Funktionsdeklarationen */
int insertWord(char** wordList, const char* word, int pos);
void sortWords(char** wordList, int words);
void swap(char** first, char** second);
void printWords(const char* const* wordList, int words);

/* insertWord fuegt ein Wort am Ende der wordlist ein. Ist das Wort
   bereits in der Liste, wird es nicht eingefügt und -1 zurückgegeben. */
int insertWord(char** wordList, const char* word, int pos) {
    int i;

    /* Wort wird ignoriert, falls es schon in der Liste ist */
    for (i = 0; i < pos; ++i) {
        if (strcmp(wordList[i], word) == 0) {
            printf("%s is already in the word list, ignored\n");
            return -1;
        }
    }

    /* Speicherallozierung und Kopieren von word */
    wordList[i] = (char *) malloc(strlen(word)+1);
    strcpy (wordList[pos], word);
    return 0;
}

/* sortWords sortiert die Woerter in wordlist mit dem
   Bubblesort Algorithmus */
void sortWords(char** wordList, int words) {
    int i, j;

    /* Bubblesort */
    for (i = words - 1; i > 0; --i) {
        for (j = 0; j < i; ++j) {
            if (strcmp(wordList[j], wordList[j+1]) > 0) {
                swap(&wordList[j], &wordList[j+1]);
            }
        }
    }
}

/* swap vertauscht die Daten, auf welche zwei Pointer zeigen */
void swap(char** first, char** second) {
    char* temp = *first;
    *first = *second;
    *second = temp;
}

/* printWords listet die Woerter auf */
void printWords(const char* const* wordList, int words) {
    int i;

    printf("Sorted word list:\n");
    for (i = 0; i < words; ++i) {
        printf("%s\n", wordList[i]);
    }
}

/* Hauptprogramm */
int main(void) {
    char* wordList[size];
    char word[20];
    int wordsInList = 0;
    int cont = 1;
    char terminator[] = "ZZZ";

    /* Einlesen des 1. Worts */
    printf("Enter words, seperated by enter, complete entry with \"ZZZ\":\n");
    scanf("%s", word);
    while (cont && (strcmp(word, terminator) != 0)) {
        if (wordsInList < size) {
            if (!insertWord(wordList, word, wordsInList)) {
                ++wordsInList;
            }
            scanf("%s", word);
        } else {
            printf("List is full (size words)\n");
            cont = 0;
        }
    }

    /* Sortieren und ausgeben der Liste */
    sortWords(wordList, wordsInList);
    printWords((const char* const*)wordList, wordsInList);
}
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <bits/stdc++.h>
#include <iostream>
#include <sched.h>
using namespace std;

// Global variable
string phraseArr;

// Checks if a word in a string starts with a letter
void *alpha(void *arg) {
    string myPhrase = phraseArr;

    string temp;
    string temp2;

    // Ranged-based for loop to determine the "words" in the string
    for (auto x : myPhrase) {
      if (x != ' ') {
        temp += x;
      }
      else {
        temp2 = temp;
        // Need to clear temp variable to allow a new word to be read in
        temp = "";

        // Checks if the first letter of temp2 is a letter
        if (isalpha(temp2[0])) {
          // If so, then print the word
          cout << "alpha: " << temp2 << endl;
        }
        else {
          // If not, yield CPU to next thread in queue
          sched_yield();
        }
      }
    }

    pthread_exit(0);
}

// Checks if a word in a string starts with a number
void *numeric(void *arg) {
    string myPhrase = phraseArr;

    string temp;
    string temp2;

    // Ranged-based for loop to determine the "words" in the string
    for (auto x : myPhrase) {
      if (x != ' ') {
        temp += x;
      }
      else {
        temp2 = temp;
        // Need to clear temp variable to allow a new word to be read in
        temp = "";

        // Checks if the first letter of temp2 is a number
        if (isdigit(temp2[0])) {
          // If so, then print the word
          cout << "numeric: " << temp2 << endl;
        }
        else {
          // If not, yield CPU to next thread in queue
          sched_yield();
        }
      }
    }

    pthread_exit(0);
}

int main (int argc, char *argv[]) {
    // Error check for input
    if (argc != 2) {
        fprintf(stderr, "usage: ./<filename> <phrase>\n");
        return -1;
    }

    // Assign input to global variable
    phraseArr = argv[1];
    // Add a space to the end of the global variable to separate end string
    // char from the last word
    phraseArr += ' ';


    // Taken from concurrent threads examples
    pthread_t p1, p2;

    pthread_create(&p1, NULL, alpha, NULL);
    pthread_create(&p2, NULL, numeric, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);


    // Finish program
    cout << "\nProgram Ending...\n";
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#include <bits/stdc++.h>
#include <iostream>
#include <sstream>
using namespace std;

string phraseArr;
vector<string> phrase;
int currIndex = 0;
int SIZE = 0;

void *alpha(void *arg) {
    while (currIndex <= SIZE) {
        string temp = phrase[currIndex];
        if (isalpha(temp[0])) {
            cout << "alpha: " << phrase[currIndex] << endl;
            currIndex++;
        } else if (temp[0] == NULL) {
            break;
        } else {
            sleep(1); 
        }
    }
    pthread_exit(0);
}

void *numeric(void *arg) {
    while (currIndex <= SIZE) {
        string temp = phrase[currIndex];
        if (isdigit(temp[0])) {
            cout << "numeric: " << phrase[currIndex] << endl;
            currIndex++;
        } else if (temp[0] == NULL) {
            break;
        } else {
            sleep(1); 
        }
    }
    pthread_exit(0);
}

int main (int argc, char *argv[]) {
    // Error check for input
    if (argc != 2) {
        fprintf(stderr, "*ERROR* usage: ./<filename> <phrase>\n");
        return -1;
    }

    phraseArr = argv[1];
    istringstream iss(phraseArr);
    // Iterates over string and adds each word / phrase to 'vector<string> phraseArr'
    while (iss) {
        string temp;
        iss >> temp;
        phrase.push_back(temp); // pushes word 'temp' to end of vector
        SIZE++;
    }

    pthread_t p1, p2;

    pthread_create(&p1, NULL, alpha, NULL);
    pthread_create(&p2, NULL, numeric, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    cout << "\nProgram Ending...\n";
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <iostream>
#include <sstream>
using namespace std;

char* phraseArr;
bool flag;
// int currIndex = 0;
// vector<string> phrase;
// int SIZE = 0;

void *alpha(void *arg) {
    istringstream iss(phraseArr);
    // do {
    //     string temp;
    //     iss >> temp;
    //     phrase.push_back(temp); // pushes word 'temp' to end of vector
    //     SIZE++;
    // } while (iss);

    // while (phrase[currIndex] < SIZE) {
    //     if (flag == true) { // last char was alpha
    //         if (isalpha(phrase[currIndex])) {
    //             cout << "alpha: " << phrase[currIndex] << endl;
    //         } else {
    //             // TODO 
    //             // cout << "not alpha: " << temp << endl; 
    //         }
    //         flag = false; // next char is alpha
    //         currIndex++;
    //     } else {
    //         sleep(1);
    //     }
    // }

    do {
        string temp;
        iss >> temp;

        if (flag == true) { // last char before space was alpha
            if (isalpha(temp[0])) {
                cout << "alpha: " << temp << endl;
            } else {
                // TODO 
                // cout << "not alpha: " << temp << endl; 
            }
            // cout << "alpha: " << temp << endl;
            flag = false; // next char is alpha
        } else {
            sleep(1);
        }
    } while (iss);
}

void *numeric(void *arg) {
    istringstream iss(phraseArr);
    // do {
    //     string temp;
    //     iss >> temp;
    //     phrase.push_back(temp); // pushes word 'temp' to end of vector
    //     SIZE++;
    // } while (iss);

    // while (phrase[currIndex] < SIZE) {
    //     if (flag == false) { // last char was alpha
    //         if (isdigit(phrase[currIndex])) {
    //             cout << "numeric: " << phrase[currIndex] << endl;
    //         } else {
    //             // TODO 
    //             // cout << "not alpha: " << temp << endl; 
    //         }
    //         flag = true; // next char is alpha
    //         currIndex++;
    //     } else {
    //         sleep(1);
    //     }
    // }

    do {
        string temp;
        iss >> temp;

        if (flag == false) { // last char before space was numeric
            if (isdigit(temp[0])) {
                cout << "numeric: " << temp << endl;
            } else {
                // TODO 
                // cout << "not numeric: " << temp << endl; 
            }
            // cout << "numeric: " << temp << endl;
            flag = true; // next char is alpha
        } else {
            sleep(1);
        }
    } while (iss);
}

int main (int argc, char *argv[]) {
    // Error check for input
    if (argc != 2) {
        fprintf(stderr, "*ERROR* usage: ./<filename> <phrase>\n");
        return -1;
    }

    phraseArr = argv[1];
    if (isalpha(phraseArr[0])) {
        flag = true; // is alpha
    } else {
        flag = false; // is numeric
    }

    pthread_t p1, p2;

    pthread_create(&p1, NULL, alpha, (void*)phraseArr);
    pthread_create(&p2, NULL, numeric, (void*)phraseArr);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    cout << "\nProgram Ending...\n";
    return 0;
}
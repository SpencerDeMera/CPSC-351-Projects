#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <bits/stdc++.h>
using namespace std;

vector<int> fibArr;
int ctr;

// Fibonacci sequence generator
void *fib (void *arg) {
    if (ctr == 0) {
        fibArr[ctr] = 0;
        pthread_exit(0); // exits thread until next loop call
    } else if (ctr == 1) {
        fibArr[ctr] = 1;
        pthread_exit(0); // exits thread until next loop call
    } else {
        fibArr[ctr] = fibArr[ctr - 1] + fibArr[ctr - 2];
        pthread_exit(0); // exits thread until next loop call
    }
}

int main (int argc, char *argv[]) {
    // Error check for input
    if (argc != 2) {
        fprintf(stderr, "usage: ./<filename> <integer value>\n");
        return -1;
    }

    // Variable for 'atoi(argv[1])' because its used so much
    int arg = atoi(argv[1]);
    // error check that a valid integer was entered
    if (arg < 0) {
        fprintf(stderr, "%d must be >= 0\n", arg);
        return -1;
    }

    // sizes and allocates fibArr
    fibArr.resize(arg);
    pthread_t *fibThreads = (pthread_t *) malloc(arg * sizeof(pthread_t));

    pthread_attr_t attr; // set of thread attributes 
    pthread_attr_init(&attr); // get the default attributes

    // For loop for creating and call threads to execute fib()
    for (ctr = 0; ctr < arg; ctr++) {
        pthread_create(&fibThreads[ctr], &attr, fib, NULL); // creates thread in fib()
        pthread_join(fibThreads[ctr], NULL); // joins threa Arr together
    }

    // Prints the fib sequence sequentially on a single line
    cout << "Calculated Fibonacci Sequence : ";
    for (int i = 0; i < arg; i++) {
        cout << fibArr[i] << ' ';
    }

    cout << "\nProgram Ending...\n";
    return 0;
}

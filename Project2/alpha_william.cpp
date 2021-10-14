#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <bits/stdc++.h>
#include <iostream>
#include <sstream>
#include <sched.h>
using namespace std;

string phraseArr;

void *alpha(void *arg) {
  string myPhrase = phraseArr;

  string temp;
  string temp2;

  // for (int i = 0; i < myPhrase.size(); i++) {
  //   if (myPhrase[i] != ' ') {
  //     temp += myPhrase[i];
  //   }
  //   else {
  //     temp2 = temp;
  //     temp = "";
  //     if (isalpha(temp2[0])) {
  //       cout << "alpha: " << temp2 << endl;
  //     }
  //     else {
  //       sched_yield();
  //       // cout << "yeet" << endl;
  //     }
  //   }
  // }

  for (auto x : myPhrase) {
    if (x != ' ') {
      temp += x;
    }
    else {
      temp2 = temp;
      temp = "";
      if (isalpha(temp2[0])) {
        cout << "alpha: " << temp2 << endl;
      }
      else {
        sched_yield();
        // cout << "yeet" << endl;
      }
    }
  }


  pthread_exit(0);
}

void *numeric(void *arg) {

  // cout << "here" << endl;
  string myPhrase = phraseArr;

  string temp;
  string temp2;

  // for (int i = 0; i < myPhrase.size(); i++) {
  //   if (myPhrase[i] != ' ') {
  //     temp += myPhrase[i];
  //   }
  //   else {
  //     temp2 = temp;
  //     temp = "";
  //     if (isdigit(temp2[0])) {
  //       cout << "numeric: " << temp2 << endl;
  //     }
  //     else {
  //       sched_yield();
  //       // cout << "yeet" << endl;
  //     }
  //   }
  // }

  for (auto x : myPhrase) {
    if (x != ' ') {
      temp += x;
    }
    else {
      temp2 = temp;
      temp = "";
      if (isdigit(temp2[0])) {
        cout << "numeric: " << temp2 << endl;
      }
      else {
        sched_yield();
        // cout << "yeet" << endl;
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

    phraseArr = argv[1];

    pthread_t p1, p2;

    pthread_create(&p1, NULL, alpha, NULL);
    pthread_create(&p2, NULL, numeric, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);


    cout << "\nProgram Ending...\n";
    return 0;
}

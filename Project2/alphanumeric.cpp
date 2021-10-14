#include <stdio.h>
 #include <stdlib.h>
 #include <ctype.h>
 #include <pthread.h>
 #include <bits/stdc++.h>
 #include <iostream>
 #include <sstream>
 using namespace std;

 char* phraseArr;
 int i = 0; //counter

 void *alpha(void *arg) {
     istringstream iss(phraseArr);

      string temp;

     do {
         iss >> temp;

         if (isalpha(temp[0])) {
             cout << "alpha: " << temp << endl;
         }

     } while (iss);
 }

 void *numeric(void *arg) {
     istringstream iss(phraseArr);

      string temp;

     do {
         string temp;

         iss >> temp;

         if (isdigit(temp[0])) {
             cout << "numeric: " << temp << endl;
         }
         
     } while (iss);
 }

 int main (int argc, char *argv[]) {
     // Error check for input
     if (argc != 2) {
         fprintf(stderr, "usage: ./<filename> <phrase>\n");
         return -1;
     }

     phraseArr = argv[1];

     pthread_t p1, p2;

     pthread_create(&p1, NULL, alpha, (void*)phraseArr);
     pthread_create(&p2, NULL, numeric, (void*)phraseArr);

     pthread_join(p1, NULL);
     pthread_join(p2, NULL);

     cout << "\nProgram Ending...\n";
     return 0;
 }

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

using namespace std;

int main(int argc, char** argv) {
	// Error check for if filename was entered
	if (argc < 2) {
		cout << "FILE NAME missing\n";
		exit(1);
	}

	// Open the file 
	int inFl = open(argv[1], O_RDONLY);
	// Error check for if file open
	if (inFl < 0) {
		cout << "\n" << "input file cannot be opened" << "\n";
		exit(1);
	}

	// Create a new file
	int outFl = creat(argv[2], O_CREAT);
	// Error check for if file created
	if (outFl < 0) {
		cout << "\n" << "output file cannot be created" << "\n";
		exit(1);
	}

	// Set offset size to 0
  	off_t pageOffset = 0;

	// Gets file size
	struct stat stats;
	cout << "File Properties: \n";
	if (stat(argv[1], &stats) == 0) {
		cout << "\tfile size: " << stats.st_size;
	} else {
		cout << "Unable to get file properties.\n";
	}
	// Save file size
	int fSize = stats.st_size;

	// Gets page size
	int pagesize = getpagesize();
	cout << endl << "\tpage size: " << pagesize << "\n";

	// Loops through pages based off filesize
	for (int i = 0; i < fSize; i += pagesize) {
		// map the file into memory
		char* inData = (char*)mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, inFl, i);
		// Error check for mapping success
		if (!inData) {
			cout << "\n" << "mapping did not succeed" << "\n";
			exit(1);
		}

		// map the file into memory
		char* outData = (char*)mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, outFl, i);
		// Error check for mapping success
		if (!outData) {
			cout << "\n" << "mapping did not succeed" << "\n";
			exit(1);
		}

		// copy pagesize amount of data to outData file
		memcpy(outData, inData, pagesize);
		munmap(inData, pagesize); // unmap the shared memory region
		munmap(outData, pagesize); // unmap the shared memory region
	}

	close(inFl); // close input file
	close(outFl); // close output file
	return 0;
}

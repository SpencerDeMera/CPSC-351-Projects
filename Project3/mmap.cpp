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

	// initialize the output file to recieve data from inFile.txt
	lseek(outFl, fSize - 1, SEEK_SET);
	write(outFl, "", 1);
	lseek(outFl, 0, SEEK_SET);

	while (fSize > 0) {
		// Setup for looping through the pages of input file
		if (fSize < pagesize) {
			pagesize = fSize;
			fSize = 0;
		} else {
			fSize -= pagesize;
		}

		// map the file into memory
		char* inData = (char*)mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, inFl, pageOffset);
		// Error check for mapping success
		if (!inData) {
			cout << "\n" << "mapping did not succeed" << "\n";
			exit(1);
		}

		// map the file into memory
		char* outData = (char*)mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, outFl, pageOffset);
		// Error check for mapping success
		if (!outData) {
			cout << "\n" << "mapping did not succeed" << "\n";
			exit(1);
		}

		// copy pagesize amount of data to outData file
		memcpy(outData, inData, pagesize);
		munmap(inData, pagesize); // unmap the shared memory region
		munmap(outData, pagesize); // unmap the shared memory region

		// shift the offsets of the in and output files
		lseek(inFl, pagesize, SEEK_SET);
		lseek(outFl, pagesize, SEEK_SET);

		// Add pagesize to offset
		// (Move onto the next page of data)
		pageOffset += pagesize;
	}

	close(inFl); // close input file
	close(outFl); // close output file
	return 0;
}

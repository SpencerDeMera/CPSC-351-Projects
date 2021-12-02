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

	// Open teh file 
	int fd = open(argv[1], O_RDWR);
	// Error check for if file open
	if (fd < 0) {
		cout << "\n" << "input file cannot be opened" << "\n";
		exit(1);
	}

	// Gets file size
	struct stat stats;
	if (stat(argv[1], &stats) == 0) {
		cout << endl << "file size " << stats.st_size;
	} else {
		cout << "Unable to get file properties.\n";
	}

	// Gets page size
	int pagesize = getpagesize();
	cout << endl << "page size is " << pagesize << "\n";
	
	// map the file into memory
	char* data = (char*)mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	// Error check for mapping success
	if (!data) {
		cout << "\n" << "mapping did not succeed" << "\n";
		exit(1);
	}

	// Print the whole file character-by-character
	for (int fIndex = 0; fIndex < pagesize; ++fIndex) {
		cout << data[fIndex];
		// if ((fIndex%1000) == 1) {
		// 	cout<<endl;
		// }
	}
	cout << endl;

	munmap(data, pagesize); // unmap the shared memory region

	close(fd); // close file
	return 0;
}

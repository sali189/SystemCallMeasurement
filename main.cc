/*
 * main.cc
 *
 *  Created on: Sep 25, 2017
 *      Author: zain
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <assert.h>
#include <time.h>
#include <sys/syscall.h>
#include <sys/time.h>
using namespace std;


int sysWrites(int bufferSize, long numberOfWrites) {

	char buffer[bufferSize];

	int fileHandle = syscall(SYS_open, "file.txt", O_CREAT|O_TRUNC|O_RDWR);

	for(int i = 0; i < numberOfWrites; i++) {
		syscall(SYS_write, fileHandle, &buffer[0], bufferSize);
	}

	 syscall(SYS_close, fileHandle);

}

int main(int argc, char* argv[]){
	clock_t start = clock();
	int r = sysWrites(4194304, 5000000);
	clock_t stop = clock();
	double elapsed = (double)(stop-start)*1000.0/CLOCKS_PER_SEC;
	printf("Time to write 1,048,576 bytes and 500 # of writes: %f \n", elapsed);
}





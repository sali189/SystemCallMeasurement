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
	int fileHandle = syscall(SYS_open, "file.txt", O_CREAT|O_TRUNC|O_WRONLY);
	for(int i = 0; i < numberOfWrites; i++) {
		syscall(SYS_write, fileHandle, &buffer[0], bufferSize);
	}
	 syscall(SYS_close, fileHandle);

}
int sysReads(int bufferSize, long numberOfReads){
	char buffer[bufferSize];
	int fileHandle = syscall(SYS_open, "file.txt", O_CREAT|O_TRUNC|O_RDONLY);
	for(auto i = 0; i<numberOfReads; i++){
		syscall(SYS_read, fileHandle, &buffer[0], bufferSize);
	}
	syscall(SYS_close, fileHandle);
}

int main(int argc, char* argv[]){
	clock_t start = clock();
	int r = sysWrites(1000, 1);
	clock_t stop = clock();
	clock_t start2 = clock();
	int q = sysReads(1000, 1);
	clock_t stop2 = clock();
	double elapsedWrite = (double)(stop-start)*1000.0/CLOCKS_PER_SEC;
	double elapsedRead = (double)(stop2-start2)*1000.0/CLOCKS_PER_SEC;
	printf("Time to write 50000 with buffer size of 1000: %f \n", elapsedWrite);
	printf("Time to read 50000 with buffer size of 1000: %f \n", elapsedRead);
}





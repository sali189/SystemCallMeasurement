/*
 * main.cpp
 *
 *  Created on: Sep 25, 2017
 *      Author: zain
 */
#include <stdio.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <sys/types.h>
#include <assert.h>
#include <vector>
#include <time.h>
#include <sys/syscall.h>
#include <sys/time.h>
using namespace std;


double timespec_to_ms(struct timespec *ts){
	return ts -> tv_sec + ts->tv_nsec/1000000000.0;
}
int sysWrites(int bufferSize, long numberOfWrites, const char *FILE) {
	char buffer[bufferSize];
	int fileHandle = syscall(SYS_open, FILE , O_CREAT|O_TRUNC|O_RDWR);
	for(int i = 0; i < numberOfWrites; i++) {
		syscall(SYS_write, fileHandle, &buffer[0], bufferSize);
	}
	 syscall(SYS_close, fileHandle);
	 return 0;
}
int sysReads(int bufferSize, long numberOfReads){
	char buffer[bufferSize];
	int fileHandle = syscall(SYS_open, "file.txt", O_CREAT|O_TRUNC|O_RDWR);
	for(auto i = 0; i<numberOfReads; i++){
		syscall(SYS_read, fileHandle, &buffer[0], bufferSize);
	}
	syscall(SYS_close, fileHandle);
	return 0;
}

int main(int argc, char* argv[]){
/*
	if(argc<7){
		cerr<<"not enough arguments: " << argv[0] << endl;
		return 1;
	}*/
	struct timespec start_time, end_time;
	int index = 0;
	for(index = 0; index<argc; index++){
		if(strncmp(argv[index], "--write_count", 13)==0){
			printf("main(): Write_count was called\n");
			clock_gettime(CLOCK_REALTIME, &start_time);
				sysWrites(1000000, 10000000, "file.txt");
				clock_gettime(CLOCK_REALTIME, &end_time);
				printf("Program took %f seconds to finish \n",timespec_to_ms(&end_time)-timespec_to_ms(&start_time));

		} else if(strncmp(argv[index],"--read_count", 12)==0){
			printf("main(): Read_count was called\n");
			clock_gettime(CLOCK_REALTIME, &start_time);
			sysReads(100000,1000000);
			clock_gettime(CLOCK_REALTIME, &end_time);
			printf("Program took %f seconds to finish \n",timespec_to_ms(&end_time)-timespec_to_ms(&start_time));
			}
		}

}



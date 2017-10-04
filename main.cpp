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
void sysWrites(int bufferSize, long numberOfWrites, const char *FILE) {
	char buffer[bufferSize];
	int fileHandle = syscall(SYS_open, FILE , O_CREAT|O_TRUNC|O_RDWR);
	for(int i = 0; i < numberOfWrites; i++) {
		syscall(SYS_write, fileHandle, &buffer[0], bufferSize);
	}
	 syscall(SYS_close, fileHandle);
}
void sysReads(int bufferSize, long numberOfReads, const char *FILE){
	char buffer[bufferSize];
	int fileHandle = syscall(SYS_open, FILE, O_CREAT|O_TRUNC|O_RDWR);
	for(auto i = 0; i<numberOfReads; i++){
		syscall(SYS_read, fileHandle, &buffer[0], bufferSize);
	}
	syscall(SYS_close, fileHandle);
}

int main(int argc, char* argv[]){
	if(argc<7){
		cerr<<"not enough arguments: " << argv[0] << endl;
		return 1;
	}

	struct timespec start_time, end_time;
	int index=1;
	if(strncmp(argv[index], "--buffer_size",13)==0) {
		char* b = argv[index+1]; 
		long bufferSize;
		bufferSize= atol(b);
		if (strncmp(argv[index+2], "--file_name",11)==0) {
			char* file= argv[index+3];
			if(strncmp(argv[index+4], "--write_count", 13)==0){
				clock_gettime(CLOCK_REALTIME, &start_time);
				char* l = argv[index+5]; 
				long numberOfWrites;	
				numberOfWrites= atol(l);		
				sysWrites(bufferSize, numberOfWrites, file);
				long total= bufferSize*numberOfWrites;
				printf("Wrote a total of %ld bytes.\n",total);
				clock_gettime(CLOCK_REALTIME, &end_time);
				printf("Program took %f seconds to finish \n",timespec_to_ms(&end_time)-timespec_to_ms(&start_time));
				} else if(strncmp(argv[index+4],"--read_count", 12)==0){
					clock_gettime(CLOCK_REALTIME, &start_time);
					char* l = argv[index+5]; 
					long numberOfReads;	
					numberOfReads= atol(l);
					sysReads(bufferSize,numberOfReads, file);
					long total= bufferSize*numberOfReads;
					printf("Read a total of %ld bytes.\n",total);
					clock_gettime(CLOCK_REALTIME, &end_time);
					printf("Program took %f seconds to finish \n",timespec_to_ms(&end_time)-timespec_to_ms(&start_time));
					}
			}
          }
}



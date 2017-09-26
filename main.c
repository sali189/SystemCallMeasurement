/*
 * main.c
 *
 *  Created on: Sep 25, 2017
 *      Author: zain
 */
#include <sys/time.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>


long nanosec(struct timeval t){
  return((t.tv_sec*1000000+t.tv_usec)*1000);
}

int main(){
  int i,j,res;
  long N_iterations=1000000;
  float avgTimeSysCallR, avgTimeSysCallW;
  struct timeval t1, t2;


  res=gettimeofday(&t1,NULL); assert(res==0);
  for (i=0;i<N_iterations; i++){
    j=syscall(SYS_read, "file.txt", O_CREAT|O_TRUNC|O_RDWR);
  }
  res=gettimeofday(&t2,NULL);   assert(res==0);
  avgTimeSysCallR = (nanosec(t2) - nanosec(t1))/(N_iterations*1.0);


  res=gettimeofday(&t1,NULL);  assert(res==0);
  for (i=0;i<N_iterations; i++){
    j=syscall(SYS_write, "file.txt", O_CREAT|O_TRUNC|O_RDWR);
  }
  res=gettimeofday(&t2,NULL);   assert(res==0);
  avgTimeSysCallW = (nanosec(t2) - nanosec(t1))/(N_iterations*1.0);


  printf("Average time for System call read: %f\n",avgTimeSysCallR);
  printf("Average time for System call write: %f\n",avgTimeSysCallW);
}


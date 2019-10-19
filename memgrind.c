#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>
#include "mymalloc.h"

//srand(time(NULL));


//A: malloc() 1 byte and immediately free it - do this 150 times
double testcaseA(){
	struct timeval begin, end;
	void* temp[4096]; //A temp array so that way we don't effect the actual memory 
	gettimeofday(&begin, NULL);
    int i;
	for(i = 0; i < 150; i++){
		temp[i] = malloc(1);
		free(temp[i]);
	}

	gettimeofday(&end, NULL);
	double elapsed = (double) (end.tv_sec - begin.tv_sec) + (double) ((end.tv_usec - begin.tv_usec)/1000000.0);
	return elapsed;
}
//B: malloc() 1 byte, store the pointer in an array - do this 150 times.
//Once you've malloc()ed 150 byte chunks, then free() the 150 1 byte pointers one by one.
double testcaseB(){
	struct timeval begin, end;
	void * temp[4096]; //A temp array so that way we don't effect the actual memory 
	gettimeofday(&begin, NULL);
    int i;
	for(i = 0; i < 150; i++){
		temp[i] = malloc(1);
	}

	for(i = 0; i < 150; i++){
		free(temp[i]);	
	}
	gettimeofday(&end, NULL);
	double elapsed = (double) (end.tv_sec - begin.tv_sec) + (double) ((end.tv_usec - begin.tv_usec)/1000000.0) ;
	return elapsed;
}



// Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer
//> do this until you have allocated 50 times
//- Keep track of each operation so that you eventually malloc() 50 bytes, in total
//> if you have already allocated 50 times, disregard the random and just free() on each
// iteration
//- Keep track of each operation so that you eventually free() all pointers
// > don't allow a free() if you have no pointers to free()
double testcaseC(){
	struct timeval begin, end;
	void * temp[4096];
    int garbadge = 8; // a garbadge address that does nothing; 
    int i;
    for(i = 0; i < 4096; i++){
        temp[i] = &garbadge;
    }
	int mallocCount = 0, inUse = 0;
	gettimeofday(&begin, NULL);
	while(mallocCount < 50){
		int r = rand() % 2; // Results in either 1 or 0 use to pick malloc or free 
        int n = rand() % 4096; //Random index 
		if(r == 0){//Malloc
            if(temp[n] == &garbadge){
	        temp[n] = malloc(1);
			mallocCount++;
            inUse++;
            }
		}
		else{ //Free 
            if(temp[n] != &garbadge){
                free(temp[n]);
                temp[n] = &garbadge;
                inUse--;
            }
		}
	}
	i = 0;
   while(inUse != 0){
      if(temp[i] != &garbadge){
           free(temp[i]);
           temp[i] = &garbadge;
           inUse--;
      }
      i++;
    }
	gettimeofday(&end, NULL);
	double elapsed = (double) (end.tv_sec - begin.tv_sec) + (double) ((end.tv_usec - begin.tv_usec)/1000000.0) ;
	return elapsed;
}
/*
Randomly choose between a randomly-sized malloc() or free()ing a pointer – do this many
 times (see below)
- Keep track of each malloc so that all mallocs do not exceed your total memory capacity
- Keep track of each operation so that you eventually malloc() 50 times
- Keep track of each operation so that you eventually free() all pointers
- Choose a random allocation size between 1 and 64 bytes
*/
double testcaseD(){
    struct timeval begin, end;
	  void* temp[4096];
    int garbadge = 8; // a garbadge address that does nothing; 
    int i;
    for(i = 0; i < 4096; i++){
        temp[i] = &garbadge;
    }
	int mallocCount = 0, inUse = 0, totalSize = 0;
	gettimeofday(&begin, NULL);
	while(mallocCount < 50){
		int r = rand() % 2; // Results in either 1 or 0 use to pick malloc or free 
        int n = rand() % 4096; //Random index 
        int randomSize = (rand() % 64) + 1;
		if(r == 0){//Malloc
            if(temp[n] == &garbadge && (totalSize + randomSize) < 4096){
            temp[n] = malloc(randomSize);
			      mallocCount++;
            inUse++;
			      totalSize = totalSize + randomSize + sizeof(Block);
            }
		}
		else{ // Free
			if(temp[n] != &garbadge){
                Block * curr = (void *) temp-1;
                totalSize = totalSize - (curr->size + sizeof(Block));
                free(temp[n]);
                temp[n] = &garbadge;
                inUse--;              
            }
		}
	}

    i = 0;
    while(inUse != 0){
        if(temp[i] != &garbadge){
            free(temp[i]);
                temp[i] = &garbadge;
                inUse--;
        }
        i++;
    }	
	gettimeofday(&end, NULL);
	double elapsed = (double) (end.tv_sec - begin.tv_sec) + (double) ((end.tv_usec - begin.tv_usec)/1000000.0) ;
	return elapsed;
}

//malloc() the entire area and free it immediately- do this 150 times
double testcaseE(){
  struct timeval begin, end;
	void* temp[4096]; //A temp array so that way we don't effect the actual memory 
	gettimeofday(&begin, NULL);
  int i = 0;
	while(i < 150){
    		temp[0] = malloc((4096-sizeof(Block)));
		free(temp[0]);
        i++;
  }
	gettimeofday(&end, NULL);
	double elapsed = (double) (end.tv_sec - begin.tv_sec) + (double) ((end.tv_usec - begin.tv_usec)/1000000.0) ;
	return elapsed;
}


//Randomly fill the entire area with randomly-sized bytes and then free until all pointers are freed
//Random allocation size between 1 to 4096 - sizeof(Block)
double testcaseF(){
  struct timeval begin, end;
	void* temp[4096]; //A temp array so that way we don't effect the actual memory 
  Block * ptr = (void *)temp;
	gettimeofday(&begin, NULL);
  int size = 0;
	while(size < 4096){
       int randomSize = (rand() % (4096 - sizeof(Block))) + 1;
		  temp[size] = malloc(randomSize);
        size = randomSize+sizeof(Block);
    }
    
    while(size > 0){
    int decrease = ptr->size+sizeof(Block);
    size = size - decrease; 
    free(temp+1);
    ptr = ptr+ptr->size;
    }
	gettimeofday(&end, NULL);
	double elapsed = (double) (end.tv_sec - begin.tv_sec) + (double) ((end.tv_usec - begin.tv_usec)/1000000.0) ;
	return elapsed;
}

int main(){
	double a = 0, b = 0,  c = 0, d = 0, e = 0, f = 0;
	int i;
  //Repeats all test cases 100 times 
	for(i = 0; i < 100; i++){
		a += testcaseA();
		b += testcaseB();
		c += testcaseC();
		d += testcaseD();
		e += testcaseE();
		f += testcaseF();
	}

	printf("Avg time for A: %f seconds\n", a/100);
	printf("Avg time for B: %f seconds\n", b/100);
	printf("Avg time for C: %f seconds\n", c/100);
	printf("Avg time for D: %f seconds\n", d/100);
	printf("Avg time for E: %f seconds\n", e/100);
	printf("Avg time for F: %f seconds\n", f/100);
	
	return 0;
}
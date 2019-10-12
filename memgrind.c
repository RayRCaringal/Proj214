#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>
#include "mymalloc.h"

int main (int argc, char **argv){
  
  printf("\n");
  
  
  //Each Test case: A is for malloc / B is for malloc store the pointer in an array and test 150 times / C is for randomly choosing a 1 byte / D randomly choose between an randomly sized malloc or freeing pointer 
  
  double a = 0;
  double b = 0;
  double c = 0;
  double d = 0;
  //two workloads of our choosing 
  double e = 0;
  double f = 0;
  
  //using the time funct from time.h
  //srand setting the seed for rand at null
  srand(time(NULL))
    
  //Error checker 
  char * p = (char *)malloc( 200 );
  
      double elapsed = (end.tv_sec - begin.tv_sec) + ((end.tv_usec - begin.tv_usec)/1000000.0);
  
  
  
//Big loop to perform the test cases 100 times and return the average  
int count = 0;
while(count != 100){
  
} 
  
  


  //      TEST CASE A
    
  gettimeofday(&begin , NULL);
  
  int i = 0;
  
  for(i = 0; i < 150 ;i++){
    
    p = malloc(1);
    free(p);
    
  }
  
  gettimeofday(&end, NULL);
  
  elapsed =     double elapsed = (end.tv_sec - begin.tv_sec) + ((end.tv_usec - begin.tv_usec)/1000000.0);
  a+=elapsed;

  //      TEST CASE B
  
  gettimeofday(&begin, NULL);
  
  void * array [150];
  
  for(i = 0;i < 150; i++){
    array[i] = malloc(1);
    
  }
  
  for(i = 0; i<150;i++){
    
    free(array[i]);
  }
  
  gettimeofday(&end, NULL);
  
  
  elapsed =     double elapsed = (end.tv_sec - begin.tv_sec) + ((end.tv_usec - begin.tv_usec)/1000000.0);
  b+=elapsed;

//     TEST CASE C
  
  
  int garbage = 8;
  for(i=0;i<150;i++){
    
    array[i] = &garbage;
    
  }

  int mallocCount = 0;
  int inUse = 0;
  int finsh = 0;
  
  while(!finsh){
    //random generator to select a byte 
    int r = rand()%20;
    
    if(mallocCount != 150 && r > 15){
      int index = rand() % 150;
      
      if(array[index] == &garbage){
        array[index] = malloc(1);
        mallocCount++;
        inUse++;
     
        
      }
      
      
    } else{
      
      int n = rand() %150;
      if (array[n] != &garbage){
        free(array[n]);
        array[n] = &garbage;
        inUse--''
        
        
      }
      
      
      
      
    }
    
    if(mallocCount==150&&inUse==0){
      
      finish = 1;
    }
    
  }
  
  
 
  gettimeofday(&end, NULL);
        elapsed = (end.tv_sec - begin.tv_sec) + ((end.tv_usec -begin.tv_usec)/1000000.0);
        c+= elapsed;
  
  
//     TEST CASE D
  
  
  gettimeofday(&begin, NULL);
  
  mallocCount = 0;
  inUse = 0;
  finish = 0;
  
  while(!finish)
  {
    
    int rando = rand()%20;
    
    if(mallocCount != 150 && rand > 15)
    {
      
      int ptr = 
    }
    
    
    
    
    
    
    
  }
  
  
  
    
    
    printf("\nAll test cases are done\n")
    
  // Displays the average time for each test case 
    printf("Avg time for A: %.10lf sec\n", a/100);
    printf("Avg time for B : %.10lf sec\n", b/100);
    printf("Avg time for E : %.10lf sec\n", c/100);
    printf("Avg time for D : %.10lf sec\n", d/100);
    printf("Avg time for E : %.10lf sec\n", e/100);
    printf("Avg time for F : %.10lf sec\n", f/100);
    
}


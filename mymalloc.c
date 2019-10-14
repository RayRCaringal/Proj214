#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"


//First-Fit Algorithim
/*
Implementation:
1- Input memory blocks with size and processes with size.
2- Initialize all memory blocks as free.
3- Start by picking each process and check if it can
   be assigned to current block. 
4- If size-of-process <= size-of-block if yes then 
   assign and check for next process.
5- If not then keep checking the further blocks.
*/

//Create Process and Block Size

//Metadata block


void intialize(){
     metadata->size = 4096-sizeof(Block);
     metadata->free = true; //True is free, false is not 
     metadata->next = NULL;
}
  
void split(Block * curr, int size){
  if(curr->size < size){
    printf("Error not enough memory\n");
    return;
  }
 Block * new = curr+size;
 new->size=(curr->size)-size-sizeof(Block);
 new->free= true;
 new->next=curr->next;
 curr->size=size;
 curr->free= false;
 curr->next=new;
}
 //Is only called in free so there should be a valid memory address
//There is at least one metadata block 
  void merge(){
    Block * curr = metadata;
    while(curr->next != NULL){
        if(curr->free == true && curr->next->free == true){
            curr->size = curr->size + curr->next->size + sizeof(Block); 
            curr->next = curr->next->next;
        }
      curr = curr->next;
    }
  }
  
  //Return pointer to memory address + 1 of metadata block
  void* myMalloc(int size){
  if(!(metadata->size)){
    intialize(metadata);
  }
  if(size <= 0){
    printf("Error \n");
    return;
  } 
   Block *curr = metadata,*prev;
    printf("Curr = %p\n", curr);
   void* result;
   while(curr->size < size || curr->free == false || curr->next != NULL){ //Incremenet through blocks till an avaible space is found
     prev = curr;
     curr = curr->next;
   }
  //Now on an avalible block 
     printf("Curr = %p\n", curr);
    if(curr->size == size && curr->free == true){ //If block size is exactly requested size then there is no more room for extra blocks
      curr->free = false;
      result = curr+1;
    }else if(curr->size > size +sizeof(Block) && curr->free == true ){ //We dont need to account for == size+blocksize since there's no more room anyways
      split(curr, size);
      result = curr+1;
    }else{ // If size requested is less than size 
      result=NULL;
      printf("Error, not enough memory");
  }
    return result;
}

void myFree(void * mem){
  if(!(mem > (void* )metadata && mem < ((void *) metadata + 4096))){
    printf("Error, memomry address is out of bounds.");
    return;
  }
  Block * curr = mem-1; //Metadata block is stored 1 memory address before
  curr->free = true;
  merge();
}  
  

int main(int argc, char** argv) {
  //printf("This is the memory address %p\n",memory); 
  //printf("This is the memory address of Block %p\n", metadata);
  //printf("Metadata->size = %d\n", metadata->size);
  char * test = myMalloc(50); 
    //printf("Metadata->size = %d\n", metadata->size);
  test[0] = 'c';
  test[1] = 'b';
  test[2] = 'a';
  //printf("Metadata->size = %d\n", metadata->size);
  printf("Test[2] = %p\n", test[2]);
  printf("Test[1] = %p\n", test[1]);
  printf("Test[0] = %p\n", test[0]);
  printf("Memory address of test = %p\n", test);
  //printf("Memory address of metadata + 1 = %p\n", metadata + 1);
  char * tester = myMalloc(111);
  tester[0] = 'f';
  tester[1] = 'e';
  tester[2] = 'd';
  printf("Test[2] = %p\n", tester[2]);
  printf("Test[1] = %p\n", tester[1]);
  printf("Test[0] = %p\n", tester[0]);
  printf("Memory address of test = %p\n", tester);
  Block * curr = metadata;
  while(curr != (void*)tester){
    curr++;
  }
  printf("Curr = %p\n", curr);
  
  
  //printf("Metadata->size = %d\n", metadata->next->size);
  
  
  //free(tester);
  //myFree();
  //printf("Tester[2] after free is = %p\n", tester[2]);
  //printf("Test[2] after free is = %p\n", test[2]);
  return;
  
  
}
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
  
void split(int size){
  if(metadata->size < size){
    printf("Error not enoug memory");
    return;
  }
 Block * new;
 new->size=(metadata->size)-size-sizeof(Block);
 new->free=1;
 new->next=metadata->next;
 metadata->size=size;
 metadata->free=0;
 metadata->next=new;
}
  
  void merge(){
     if(metadata->next == NULL){
         metadata->free = true;
         return;
     } 
    Block * curr = metadata, * prev; 
    while(curr ->next != NULL){
        if(curr->free == false && curr->next->free == false){
            curr->size = curr->size + curr->next->size + sizeof(Block); 
            curr->next = curr->next->next;
        }
      prev = curr;
      curr->next = curr->next->next;
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
   void* result;
   while(curr->size < size || curr->free == false || curr->next != NULL){ //Incremenet through blocks till an avaible space is found
     prev = curr;
     curr = curr->next;
   }
  //Now on an avalible block 
    if(curr->size == size && curr->free == true){ //If block size is exactly requested size then there is no more room for extra blocks
      curr->free = false;
      result = curr+1;
    }else if(curr->size > size +sizeof(Block) && curr->free == true ){ //We dont need to account for == size+blocksize since there's no more room anyways
      split(size);
      result = curr+1;
    }else{ // If size requested is less than size 
      result=NULL;
      printf("Error, not enough memory");
  }
    return result;
}

void myFree(){
    if(metadata->next == NULL){
        metadata->free = true;
        return;
    }
    Block * curr = metadata;
    while(curr->next != NULL){
        merge(curr);
        curr->free = true;
    }

}  
  

int main(int argc, char** argv) {
  printf("This is the memory address %p\n",memory); 
  printf("This is the memory address of Block %p\n", metadata);
  char * test = myMalloc(50); 
  test[0] = 'c';
  test[1] = 'b';
  test[2] = 'a';
  printf("Test[2] = %p\n", test[2]);
  printf("Test[1] = %p\n", test[1]);
  printf("Test[0] = %p\n", test[0]);
  printf("Memory address of test = %p\n", test);
  char * tester = malloc(sizeof(char) * 50);
  tester[0] = 'f';
  tester[1] = 'e';
  tester[2] = 'd';
  printf("Test[2] = %p\n", tester[2]);
  printf("Test[1] = %p\n", tester[1]);
  printf("Test[0] = %p\n", tester[0]);
  printf("Memory address of test = %p\n", tester);
  return;
  
  
}
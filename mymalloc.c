#include <stdio.h>
#include <stdlib.h>
#include<stddef.h>

typedef int bool;
#define true 1
#define false 0


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
typedef struct block Block{
  struct block{
  type_t size;
  bool free;
  block next;  
};

const char memory[4096];


void intialize(block metadata){
     metadata->size = 4096-sizeof(Block);
     metadata->free = true; //True is free, false is not 
     metadata->next = NULL;
}
  
void split(Block *metadata, size_t size){
  if(metadata->size < size){
    printf("Error not enoug memory");
    return;
  }
 new->size=(metadata->size)-size-sizeof(Block);
 new->free=1;
 new->next=metadata->next;
 metadata->size=size;
 metadata->free=0;
 metadata->next=new;
}
  
  void merge(Block * metadata){
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
  char *MyMalloc(Block *metadata,size_t size){
  if(metadata->size == NULL){
    printf("Error \n");
    return
  } 
   Block *curr = metadata,*prev;
   char *result;
   while(curr->size < size || curr->free == false || curr->next != NULL){ //Incremenet through blocks till an avaible space is found
     prev = curr;
     curr = curr->next;
   }
  //Now on an avalible block 
    if(curr->size == size){ //If block size is exactly requested size then there is no more room for extra blocks
      curr->free = false;
      result = curr+1;
    }else if(curr->size > size +sizeof(Block)){ //We dont need to account for == size+blocksize since there's no more room anyways
      split(curr, size);
      result = curr+1;
    }else{
      result=NULL;
  }
    return result;
}
  

int main(int argc, char** argv) {
}
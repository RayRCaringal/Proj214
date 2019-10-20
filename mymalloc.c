#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

bool initalized = false;
static char memory[4096];
Block * metadata  = (void*) memory;

void intialize(){
     metadata->size = 4096-sizeof(Block); // Inital size is 4080 
     metadata->free = true; //True is free, false is not 
     metadata->next = NULL;
}

//Splits the metadata block into two, left side is the requested memory right side is remaining memory, points towards null 
void split(Block * curr, int size, char * file, int line){
 if(curr->size < size){
   printf("Error in %s line %d: Not Enough Memory. Not Enough Space\n", file, line);
    return;
  }
 Block * new = (void *)curr + size + sizeof(Block); 
 new->size=(curr->size)-(size+sizeof(Block));
 new->free= true;
 new->next= NULL;
 curr->size = size;
 curr->free= false;
 curr->next=new;
}
/*
We cannot remove data blocks from the linked list and merge them back with total memory, because we cannot change the memory address
of Metadata blocks that are ahead. Instead we should check for metadatablocks that are next to each other that are free and fuse those.
*/

  //Merges adjacent metadata blocks in order to save space 
  void merge(){
    Block * curr = metadata;
    if(curr->next == NULL){ // There are at least 2 blocks when memory is allocated 
      return;
    }
    while(curr->next->next != NULL){ //Check for ->next->next caue we're looking at two differnet blocks, also this works for if there is only one metadata block
        if(curr->free == true && curr->next->free == true){
            curr->size = curr->size + curr->next->size + sizeof(Block); //We need to include the metadata block as well as the data's size
            curr->next = curr->next->next;
            return;
        }
      curr = curr->next;
    }
  }

//Looks for an avalible block that is not free and has adequate room
Block * get_avalible(int size){
  Block * avalible = metadata;
  while((avalible->size < size || avalible->free == false) && avalible->next != NULL){
     avalible =  avalible->next;
  }
  return avalible;
}

  //Return pointer to memory address + 1 of metadata block
  void* mymalloc(int size, char * file, int line){
  if(initalized == false){ //Check if the metadata is initalized 
    intialize();
    initalized = true;
  }
  if(size <= 0 || size > (4096 - sizeof(Block)) ){ 
    printf("Error in %s line %d: Invalid Size\n", file, line);
    return NULL;
  } 
   Block * curr = get_avalible(size);
   void* result;
   if(curr->size == size){ //If block size is exactly requested size then there is no more room for extra blocks
      curr->free = false;
      result = (void *)curr+1;
    }else if(curr->size > size +sizeof(Block)){ //Take into account the next metadata block 
      split(curr, size, file, line);
      result = (void *)curr+1;
    }else{ // If size requested is less than size 
      result=NULL;
      printf("Error in %s line %d: Not Enough Memory\n", file, line);
  }
    return result;
}
//Check if memory address is connected to a metadata block
bool check(void * mem){
  Block * temp = metadata;
  while(temp->next != NULL){
     if(temp == mem-1){
       return true;
     }
    temp = temp->next;
  }
  return false;
}

void myfree(void * mem, char * file, int line){
 if(!(mem > (void* )metadata && mem < ((void *) metadata + 4096))){
    printf("Error in %s line %d: Memomry Address Is Out Of Bounds.\n", file, line);
    return;
  }
  if(check(mem) == true){
    Block * curr = mem-1; //Metadata block is stored 1 memory address before
    curr->free = true;
    merge();
  }
}  
  
int count(){
  Block * temp = metadata;
  int count = 0;
  while(temp->next != NULL){
    count++;
    temp = temp->next;
  }
  return count;
}

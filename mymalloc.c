#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"


void intialize(){
     metadata->size = 4096-sizeof(Block); // Inital size is 4080 
     metadata->free = true; //True is free, false is not 
     metadata->next = NULL;
}
  
//Splits the metadata block into two, left side is the requested memory right side is remaining memory, points towards null 
void split(Block * curr, int size, char * file, int line){
 if(curr->size < size){
    printf("Error in %s line %d: Not Enough Memory\n", file, line);
    return;
  }
 printf("Curr address is = %p\n", curr);
 Block * new = (void *)curr + size + sizeof(Block); 
 new->size=(curr->size)-(size+sizeof(Block));
 printf("New address is = %p\n", new);
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

  //Fuses metadata blocks that are adjacent to each other 
  void merge(){
    Block * curr = metadata;
    if(curr->next == NULL){ // There are at least 2 blocks when memory is allocated 
      return;
    }
    while(curr->next != NULL){
        if(curr->free == true && curr->next->free == true){
            curr->size = curr->size + curr->next->size + sizeof(Block); //We need to include the metadata block as well as the data's size
            curr->next = curr->next->next;
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
  if(init == false){ //Check if the metadata is initalized 
    intialize(metadata);
    init = true;
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
  while(curr->next == NULL){
     if(curr == mem-1){
       return true;
     }
    curr = curr->next;
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

int main(int argc, char** argv) {

  printf("This is the memory address %p\n",memory); 
  printf("Size of block = %zu\n", sizeof(Block));
  char * test = malloc(10);
  test[0] = 'c';
  test[1] = 'b';
  test[2] = 'a';
  printf("Memory address of test = %p\n", test);
  printf("Test[2] = %p\n", &test[2]);
  printf("Test[1] = %p\n", &test[1]);
  printf("Test[0] = %p\n", &test[0]);
  char * tester = malloc(20);
  tester[0] = 'f';
  tester[1] = 'e';
  tester[2] = 'd';
  printf("Memory address of tester = %p\n", tester);
  printf("Tester[2] = %p\n", &tester[2]);
  printf("Tester[1] = %p\n", &tester[1]);
  printf("Tester[0] = %p\n", &tester[0]);
  char * testing = malloc(30);
  printf("Count = %d\n", count());
  free(tester);
  printf("Count = %d\n", count());
  free(testing);
  printf("Count = %d\n", count());

  return 0;
  
  
}
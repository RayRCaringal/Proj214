#ifndef MYMALLOC_H
#define MYMALLOC_H


typedef int bool;
#define true 1
#define false 0


typedef struct block Block;
  struct block{
  int size;
  bool free;
  Block * next;  
};

static char memory[4096];
Block * metadata = (void*) memory;


void intialize();
void split(Block * curr, int size);
void merge();
void* myMalloc(int size);
void myFree();


//#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
//#define free( x ) myfree( x, __FILE__, __LINE__ )

#endif
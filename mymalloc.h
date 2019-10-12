#ifndef MYMALLOC_H
#define MYMALLOC_H

typedef struct block Block;
  struct block{
  int size;
  bool free;
  Block * next;  
};

static char memory[4096];
Block * metadata = (void*) memory;


void intialize(Block *metadata);
void split(Block *metadata, size_t size);
void merge(Block * metadata);
void* myMalloc(Block *metadata,size_t size);
void myFree(Block * metadata);


#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )

#endif MYMALLOC_H
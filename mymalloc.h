#ifndef MYMALLOC_H
#define MYMALLOC_H


typedef int bool;
#define true 1
#define false 0

extern bool initalized;

typedef struct block Block;
  struct block{
  int size;
  bool free;
  Block * next;  
};

#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )

extern Block * metadata;


void intialize();
void split(Block *, int, char *, int);
void merge();
Block * get_avalible(int);
void* mymalloc(int, char *, int );
bool check(void * mem);
void myfree(void *, char *, int );


#endif
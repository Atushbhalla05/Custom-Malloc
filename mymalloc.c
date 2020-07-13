#include <stdio.h>
#include <unistd.h>
#include "mymalloc.h"

// MACRO FOR SIZE OF HEADER STRUCTURE
#define HEADER_SIZE sizeof(struct Memory)

// ENDS OF LINKED LIST
struct Memory *head = NULL;
struct Memory *tail = NULL;

// CUSTOM MALLOC
void *my_lastfit_malloc(int size){

  struct Memory *temp;

  // INVALID INPUT TO MALLOC
  if(size <=0){
    return  NULL;
  }
  temp = getMemory(size);
  // SUFFICIENTLY LARGE FREE SPACE IS FOUND
  if(temp){
    temp->free = 0;
    return temp + 1;
  }

  // MOVING BRK
  void *space = sbrk(size + HEADER_SIZE);

  // SBRK FAILED IF CASE
  if(space == (void *) -1){
    return NULL;
  }

  //ASSIGNING STUFF TO HEADER
  temp = space;
  temp->free = 0;
  temp->next = NULL;
  temp->size = size;

  // IF CASE FOR FIRST MALLOC DATA
  if(head == NULL){
    temp->prev = NULL;
    head = temp;
  }
  // TAIL ALREADY SET
  if(tail != NULL){
    temp->prev = NULL;
    tail->next = temp;
  }
  else{
    // ONLY 1 MALLOCED SPACE MEANING
    //TAIL AND HEAD AT THE SAME SPOT
    tail = head;
  }
  tail = temp;

  //RETURN TEMP + 1 BECAUSE WE WANT
  //TO ADD ONE BYTE WHICH WILL GO
  //TO THE NEXT ADDRESS
  return temp + 1;

}

// MY FREE FUNCTION
void my_free(void *ptr){

  // INVALID FREE INPUT
  if(ptr == NULL){
    return;
  }
  // GETTING PTR-1 BECAUSE WE DID TEMP + 1 IN MALLOC
  struct Memory *freeSpace =  (struct Memory *)ptr - 1;

  // IF ONE NODE OF MEMORY LEFT
  if(head == tail){
    head = NULL;
    tail = NULL;
  }
  else{
    struct Memory *memoryAt = head;

    // GOING TO THE END THE LINKED LIST
    while(memoryAt->next != tail){
      // 2 FREES TOGTHER MERGING
      if(memoryAt->free && memoryAt->next->free){
        // SAVING THE SIZE
        memoryAt->size += memoryAt->next->size + HEADER_SIZE;
        memoryAt->next = memoryAt->next->next;

        //DEALLOCATING
        sbrk(0 - (memoryAt->size + HEADER_SIZE));
      }
      memoryAt = memoryAt->next;
    }
    tail = memoryAt;
    tail->next = NULL;
  }
  sbrk(0 - (freeSpace->size + HEADER_SIZE));
}

// GO TO THE NEXT FREE MEMORY WTH ENOUGH SPACE
struct Memory *getMemory(int size){

  //LOOP STARTS FROM TAIL AS WE ARE MOVING DOWNT THE STACK
  struct Memory *memoryAt = tail;
  // WHILE LOOP TILL THE END
  while(memoryAt != NULL){
    if (memoryAt->free && memoryAt->size >= size){
			return memoryAt;
    }
		memoryAt = memoryAt->prev;
  }
  return NULL;
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

//include your code
#include "mymalloc.h"

//replace malloc here with the appropriate version of mymalloc
#define MALLOC my_lastfit_malloc
//replace free here with the appropriate version of myfree
#define FREE my_free

void test3(){
	int *a = (int *)MALLOC(sizeof(int));
	a[0] = 5;
	a[1] = 6;
	printf("\na[0] assgined %d\n", a[0]);
	printf("a[1] assgined %d\n", a[1]);
	printf("brk after a assigned: %p\n", sbrk(0));

	int *b = (int *)MALLOC(sizeof(int));
	b[0] = 10;
	b[1] = 11;
	printf("b assgined\n");
	printf("brk after b assigned: %p\n", sbrk(0));

	char *c = (char *)MALLOC(sizeof(char));
	c = "ATUSH BHALLA";
	printf("c assgined %s\n", c);
	printf("c assgined\n");
	printf("brk after c assigned: %p\n", sbrk(0));

	FREE(c);
	printf("c freed\n");
	printf("brk after c freed: %p\n", sbrk(0));

	FREE(b);
	printf("b freed\n");
	printf("brk after b freed: %p\n", sbrk(0));

	FREE(a);
	printf("a freed\n");
	printf("brk after a freed: %p\n", sbrk(0));
}

int main(){
	printf("brk before  test3: %p\n", sbrk(0));
	test3();
	printf("brk after  test3: %p\n", sbrk(0));
  return 0;
}

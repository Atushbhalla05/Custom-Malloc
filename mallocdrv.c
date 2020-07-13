/*
	This is a minimal test case for malloc/free. This is NOT
	a complete, 100% coverage set of test cases. Your test cases
	should be much more complete. The value of this file is to
	remind you to test not just by calling your malloc and free
	implementations, but to also write to the memory that you allocate.

	If you don't write to the memory you allocate, the CPU and OS
	will never tell you your allocation wasn't correctly made by
	crashing. You just moved a pointer (brk) back and forth. It's
	in using the space that you test your allocations.

	To use, change the #defined values below from malloc to
	my_firstfit_malloc and my_free and change TIMES to a reasonable
	value. Compile this file with your C file containing the
	implementation of your malloc and free and link them together by:

	gcc -m32 -o malloctest mallocdrv.c mymalloc.c
*/

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

//You can adjust how many things are allocated
#define TIMES 10

//If you want to make times bigger than 256, remove the call to qsort and do something else.
//Then remove this check.
#if TIMES >= 256
	#error "TIMES is too big, qsort will switch to mergesort which requires a temporary malloc()ed array"
#endif

//Do not modify below here
struct tree {
	int data;
	struct tree *left;
	struct tree *right;
};

void freetree(struct tree *root)
{
	if(root->left != NULL)
		freetree(root->left);
	if(root->right != NULL)
		freetree(root->right);
	FREE(root);
}

void randominsert(struct tree *head, struct tree *new)
{
	int way;
	struct tree *curr, *prev;
	prev = NULL;
	curr = head;

	while(curr != NULL)
	{
		prev = curr;
		way = rand()%2;
		if(way == 0)
		{
			curr = curr->left;
		}
		else
		{
			curr = curr->right;
		}
	}
	if(way == 0)
		prev->left = new;
	else
		prev->right = new;
}

void printtree(struct tree *head)
{
	struct tree *curr = head;
	if(head == NULL)
		return;

	printtree(curr->left);
	printf("%d\n", curr->data);
	printtree(curr->right);
}

void test1()
{
	int i;
	//printf("brk at: %p\n", sbrk(0));
	struct tree *head = (struct tree *)MALLOC(sizeof(struct tree));
	head->data = 0;
	head->left = NULL;
	head->right = NULL;

	for(i=1;i<TIMES;i++)
	{
	//	printf("brk at: %p\n", sbrk(0));
		struct tree *new = (struct tree *)MALLOC(sizeof(struct tree));
		new->data = i;
		new->left = NULL;
		new->right = NULL;
		randominsert(head, new);
	}

	printtree(head);
	freetree(head);
}

int comp(const void *a, const void *b)
{
	return *((int *)a) - *((int *)b);
}

void test2()
{
	int *a;
	int i;

	a = (int *)MALLOC(TIMES * sizeof(int));

	for(i=0;i<TIMES;i++)
	{
		a[i] = rand()%TIMES + 1;
	}

	qsort(a, TIMES, sizeof(int), comp);

	for(i=0;i<TIMES;i++)
	{
		printf("%d\n", a[i]);
	}

	FREE(a);

}
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

int main()
{
	srand((unsigned int)time(NULL));

	//For default malloc, the number printed here will not match the two
	//below. For your malloc, all three should match. (The real malloc
	//steals some space that it never returns. Yours should always be
	//removing everything it creates and reducing brk).
	printf("original val brk: %p\n", sbrk(0));
	test1();
	printf("brk after  test1: %p\n", sbrk(0));
	test2();
	printf("brk after  test2: %p\n", sbrk(0));
	test3();
	printf("brk after  test3: %p\n", sbrk(0));
	return 0;
}

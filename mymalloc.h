// STRUCTURE OF HEADER_MEMORY
struct Memory{
 int size;
 int free;
 struct Memory *next;
 struct Memory *prev;
};
//MY_MALLOC
void *my_lastfit_malloc(int size);
//MYFREE
void my_free(void  *ptr);
// HELPER FUNCTION TO GET NEXT SPACE WITH ENOUGH SIZE
struct Memory *getMemory(int size);

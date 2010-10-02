#include <stdio.h>
#include <stdlib.h>


typedef unsigned char u8_t;

#define MEM_CHUNK_IN_USE (1)
//#define MEM_CHUNK_FREE (0)

typedef struct mem_chunk 
{
  size_t size;
  struct mem_chunk * next;
  struct mem_chunk * prev;
  u8_t flags;

} memchunk_t;



#define HEAP_SIZE (4096)
char _heap_start[HEAP_SIZE];

memchunk_t* _memchunks_head;

void* malloc(size_t);
void malloc_init(void);
void print_memory_chunks(void);
void print_chunk(memchunk_t *);

void malloc_init()
{
  int i;

  for (i = 0; i < HEAP_SIZE; i++)
  {
    _heap_start[i] = ' ';
  }

  _memchunks_head = (memchunk_t *)_heap_start;
#ifdef MALLOC_DEBUG_EXTRA
  printf("Heap starts @ 0x%llx (%llu)\n", (unsigned long long)_heap_start, (unsigned long long)_heap_start);
  printf("Heap ends @ 0x%llx (%llu)\n", (unsigned long long)(& _heap_start[HEAP_SIZE-1]), (unsigned long long)(& _heap_start[HEAP_SIZE - 1]));
#endif

  _memchunks_head->size = HEAP_SIZE;
  _memchunks_head->flags = 0; 

  // At the begining we have no next and prev chunks (there are only one chunk)
  _memchunks_head->next = NULL; 
  _memchunks_head->prev = NULL; 
}

void* malloc(size_t size)
{
  memchunk_t * _mcp, * _nmcp;
  size_t flen, nsize;

  // First step:
  // We need to find first free memory chunk of bigger or equal size.
  // Becouse we have extra overhead, so we're looking for (size + overhead) chunk. 
  
  flen = size + sizeof(memchunk_t);

#ifdef MALLOC_DEBUG_EXTRA
  printf("\n--------------------------------------------------------------------------------\n");
  printf("Allocating %llu bytes chunk (actualy requested %llu)", (unsigned long long)flen, (unsigned long long)size);
#endif

  for (_mcp = _memchunks_head;
        !(_mcp && (_mcp->flags == 0) && (_mcp->size >= flen)); 
          _mcp = _mcp->next
#ifdef MALLOC_DEBUG_EXTRA
          , printf(".")
#endif
        ); 

#ifdef MALLOC_DEBUG_EXTRA
  printf("\n");
#endif

  // if there is no free chunks...
  if (!_mcp)
  {
#ifdef MALLOC_DEBUG_EXTRA
    printf("We have no free memory chunks. Sorry..\n");
#endif
    return NULL;
  }

#ifdef MALLOC_DEBUG_EXTRA
  printf("Found %llu bytes sized free chunk:\n", (unsigned long long)_mcp->size);
  print_chunk(_mcp);
#endif

  if (_mcp->size > flen)
  {
    // We found bigger shunk and we need to split it in two peaces
    // where first be allocated and second is free
    // found freechunk : [|size_t s|next|prev|..... data ....|]
    
#ifdef MALLOC_DEBUG_EXTRA
    printf("\t It is bigger (need %llu, found %llu)\n\t Splitting:\n", (unsigned long long)flen, (unsigned long long)_mcp->size); 
#endif

    nsize = _mcp->size - flen; // TODO: maybe it will be nice if we check new chunk size and if it smaller or equal than sizeof(memchunk_t), then do not split founded chunk in two chunks

#ifdef MALLOC_DEBUG_EXTRA
    printf("\t New free chunk size is %llu bytes\n", (unsigned long long)nsize);
#endif

    _nmcp = (void*)_mcp + flen; 
    _nmcp->size = nsize; 
    _nmcp->flags = 0;
    _nmcp->next = _mcp->next;
    _nmcp->prev = _mcp;

#ifdef MALLOC_DEBUG_EXTRA
    printf("_nmcp:\n");
    print_chunk(_nmcp);
#endif

    _mcp->next = _nmcp;
    _mcp->flags |= MEM_CHUNK_IN_USE;
    _mcp->size = flen;

#ifdef MALLOC_DEBUG_EXTRA
    printf("returning chunk:\n");
    print_chunk(_mcp);
    printf("EOM\n\n");
#endif
  }

  return (void*)_mcp+sizeof(memchunk_t);
}

void print_chunk(memchunk_t * chunk)
{
    printf("\t chunk is @ 0x%llx (%llu) or %llu bytes from heap start\n", (unsigned long long)chunk, (unsigned long long)chunk, (unsigned long long)((void *)chunk - (void *)_heap_start));
    printf("\t chunk->size=%llu\n", (unsigned long long)chunk->size);
    printf("\t chunk->next=0x%llx (%llu)\n", (unsigned long long)chunk->next, (unsigned long long)chunk->next);
    printf("\t chunk->prev=0x%llx (%llu)\n", (unsigned long long)chunk->prev, (unsigned long long)chunk->prev);
    printf("\t chunk->flags=%llu\n", (unsigned long long)chunk->flags);
}
void print_memory_chunks()
{
  memchunk_t * _mcp;
  unsigned long long i  = 0;

  // Traverse whole memory chunk list and print it's information
  for (_mcp = _memchunks_head; _mcp;  _mcp = _mcp->next, i++)
  {
    printf("Faund chunk:\n");
    print_chunk(_mcp);
  }

  printf("Total chunk count: %llu\n", i);
}

int main()
{
  void * ptr;
  int i, s, d;
  malloc_init();

  for (i = 0; i < 100; i++)
  {
    printf("premalloc %d\n", i);
    ptr = malloc(64);
    printf("postmalloc %d\n", i);
  }

  printf("\n\nPRINTING CHUNKS:\n");
  print_memory_chunks();

  return 0; // To make compiler happy
}


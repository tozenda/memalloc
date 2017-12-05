#ifndef __MEM_ALLOC_H
#define __MEM_ALLOC_H

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_INDEX 20
#define HEAP_SIZE (1 << MAX_INDEX)

typedef struct fb fb;
struct fb {
  size_t size ;
  void *adresse;
  struct fb *next ;
} ;

char mem_heap[HEAP_SIZE];
int bool_init;
fb *debut; // = malloc(HEAP_SIZE);

void mem_init();
void *mem_alloc(size_t size);
void mem_free(void *zone, size_t size);
void mem_show(void (*print)(void *zone, size_t size));

#endif

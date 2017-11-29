#include "alloc.h"

void mem_init(){
	debut = (fb *) mem_heap;
	debut->size = HEAP_SIZE;
	debut->next = NULL;
}

void *mem_alloc(size_t size){

	fb *a = debut;
	printf("adresse de a %p\n", &a);
	printf("size de a %d\n", a->size);
	printf("size %d\n", size);

	while(a!=NULL){

		if(a->size >= size){
			printf("c est bon\n");

		}

		else{
			printf("trouvé de bloc\n");
			return NULL;
		}

		a = a->next;
		printf("bloc pas assez grand\n");
	}
}

void mem_free(void *zone, size_t size){

}

void mem_show(void (*print)(void *zone, size_t size)){

}

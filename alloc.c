#include "alloc.h"

void mem_init(){
	fb init;
	init.size = HEAP_SIZE;
	init.next = NULL;
	debut = (fb *) mem_heap;
	*debut = init;
	bool_init = 1;
}

void *mem_alloc(size_t size){
	printf("COUCOUCOCUOCOCUOCUOCUOCUOCUCO %d", debut->size);
	/*if(bool_init){
		fb *a = debut;
		while(a->next!=NULL || a->size>size+2*sizeof(long)){
			a = a->next;
		}
		if(a->size>size+2*sizeof(long)){
			return NULL;
		}
		else{
			return NULL;
		}
	}
	else{
		printf("memoire pas initialisée");
		return(NULL);
	}*/
}

void mem_free(void *zone, size_t size){

}

void mem_show(void (*print)(void *zone, size_t size)){

}

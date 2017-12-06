#include "alloc.h"

void mem_init(){
	debut = (fb *) mem_heap;
	debut->size = HEAP_SIZE;
	debut->next = NULL;
	debut->adresse = mem_heap;
	// printf("adresse de debut %p\n", debut);
	// printf("adresse de memheap %p\n", mem_heap);
	// printf("adresse de debut struct %p\n", debut->adresse);
}

void *mem_alloc(size_t size){
	fb *adr = debut;

	while(adr!=NULL){

		if(adr->size >= size){		//+sizeof(fb *))

			adr->size -= size; // a += size; pas nécessaire si on alloue à la fin du bloc de mémoire
			return (void *)adr + adr->size;				// pas besoin de retirer la taille car on a deja mofiie a->size
		}

		adr = adr->next;
	}

	return NULL;
}

void mem_free(void *zone, size_t size){

	fb *adr = debut;
	int free_done = 0;
	fb *adr2 = debut;
	int sauv_size;

	/* 4 cas : bloc a libérer entre
		- deux bloc alloués -> créer un nouveau bloc
			bloc non alloué au dessus -> le rajouter au bloc du haut
			bloc non alloué au dessous -> fusionner les deux blocs
			2 bloc non alloués -> GIGA fusion
	*/
	while(adr!=NULL){

		if((void *) adr + adr->size == zone){	// cas 2
			printf("on a un bloc avant la zone à libérer\n");
			adr->size += size;
			free_done = 1;
			if(adr->next != NULL){
				adr2 = adr->next;
				if ((void *)adr2 == zone + size){ // cas 4FUSION
					printf("on a un bloc après la zone à libérer 2\n");
					adr->size += adr2->size;
					adr->next = adr2->next;
				}
			}
			break;
		}

		printf("size initial %d\n", adr->size);
		if((void *)adr - size == zone){ // cas 3 BUG on modif l adresse de a mais son préc pointe vers une adre fausse du coup
			free_done = 1;
			fb *new_bloc;
			new_bloc = zone;
			new_bloc->size = size + adr->size;
			adr2->next = new_bloc;
			new_bloc->next = adr->next;
			break;
		}

		adr2 = adr;
		adr = adr->next;
	}

	if(!free_done){ // cas 1
		printf("Le bloc est entre deux blocs\n");

		fb *new_bloc;
		new_bloc = zone;
		new_bloc->size = size;
		adr = debut;

		while(adr!=NULL){
			if ((void *)adr < zone){
				adr2 = adr;
				adr = adr->next;
			}
			else{
				break;
			}
		}
		new_bloc->next = adr;
		adr2->next = new_bloc;
	}
}

void mem_show(void (*print)(void *zone, size_t size)){
	fb *adr = debut;

	while(adr!=NULL){
		print((void *)adr, adr->size);
		adr=adr->next;
	}
}

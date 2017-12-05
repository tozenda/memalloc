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
	fb *a = debut;

	while(a!=NULL){

		if(a->size > size+sizeof(fb *)){

			a->size -= size; // a->adresse += size; pas nécessaire si on alloue à la fin du bloc de mémoire
			return a->adresse+ a->size;				// pas besoin de retirer la taille car on a deja mofiie a->size
		}

		a = a->next;
	}

	return NULL;
}

void mem_free(void *zone, size_t size){

	fb *a = debut;
	fb *a2;
	int free_done = 0;
	void *adr_prec;

	/* 4 cas : bloc a libérer entre
		- deux bloc alloués -> créer un nouveau bloc
			bloc non alloué au dessus -> le rajouter au bloc du haut
			bloc non alloué au dessous -> fusionner les deux blocs
			2 bloc non alloués -> GIGA fusion
	*/
	while(a!=NULL){
		if(a->adresse < zone){
			adr_prec = a->adresse;
		}

		if(a->adresse+a->size == zone){	// cas 2
			printf("on a un bloc avant la zone à libérer\n");
			a->size += size;
			free_done = 1;
			if(a->next != NULL){
				a2 = a->next;
				if (a2->adresse == zone + size){ // cas 4FUSION
					printf("on a un bloc après la zone à libérer 2\n");
					a->size += a2->size;
					a->next = a2->next;
				}
			}

		}

		if(a->adresse-size == zone){ // cas 3
			printf("on a un bloc après la zone à libérer\n");
			free_done = 1;
			a = a->adresse - size;
			a->adresse -= size;
			a->size += size;
		}

		a = a->next;
	}

	if(!free_done){ // cas 1
		printf("Le bloc est entre deux blocs\n");

		fb *new_bloc;
		new_bloc = zone;
		new_bloc->adresse = zone;
		new_bloc->size = size;
		a = debut;

		while(a->adresse!=adr_prec){
			a = a->next;
		}
		new_bloc->next = a->next;
		a->next = new_bloc;
	}
}

void mem_show(void (*print)(void *zone, size_t size)){
	fb *a = debut;

	while(a!=NULL){
		print(a->adresse, a->size);
		a=a->next;
	}
}
